#include <fstream>
#include <sstream>
#include <iostream>

int offset = 0;


// DataManipulator.cpp

#include "DataManipulator.hpp"
#include "../CustomTypes/Date_DDMMYYYY_Type.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "ConstraintValidator.hpp"

// Helper: read all values from a column file into a vector of strings
static bool readColumnFile(const std::string &path,
                           const std::string &type,
                           std::vector<std::string> &outValues)
{
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        std::cerr << "Unable to open column file for reading: " << path << std::endl;
        return false;
    }

    outValues.clear();
    if (type == "int") {
        int64_t v;
        while (in.read(reinterpret_cast<char*>(&v), sizeof(v))) {
            outValues.push_back(std::to_string(v));
        }
    }
    else if (type == "float") {
        double v;
        while (in.read(reinterpret_cast<char*>(&v), sizeof(v))) {
            outValues.push_back(std::to_string(v));
        }
    }
    else if (type == "Date_DDMMYYYY_Type") {
        Date_DDMMYYYY_Type d;
        while (in.read(reinterpret_cast<char*>(&d), sizeof(d))) {
            // normalize to YYYY-MM-DD
            char buf[11];
            snprintf(buf, sizeof(buf), "%04d-%02d-%02d", d.year, d.month, d.day);
            outValues.push_back(buf);
        }
    }
    else { // string
        while (true) {
            size_t len;
            if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
            std::string s(len, '\0');
            if (!in.read(&s[0], len)) break;
            outValues.push_back(s);
        }
    }

    in.close();
    return true;
}

// Helper: write all values (string repr) back to the column file
static bool writeColumnFile(const std::string &path,
                            const std::string &type,
                            const std::vector<std::string> &values)
{
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out) {
        std::cerr << "Unable to open column file for writing: " << path << std::endl;
        return false;
    }

    for (const auto &s : values) {
        if (type == "int") {
            int64_t v = std::stoll(s);
            out.write(reinterpret_cast<const char*>(&v), sizeof(v));
        }
        else if (type == "float") {
            double v = std::stod(s);
            out.write(reinterpret_cast<const char*>(&v), sizeof(v));
        }
        else if (type == "Date_DDMMYYYY_Type") {
            // parse YYYY-MM-DD
            Date_DDMMYYYY_Type d = Date_DDMMYYYY_Type::parse(s);
            out.write(reinterpret_cast<const char*>(&d), sizeof(d));
        }
        else { // string
            size_t len = s.size();
            out.write(reinterpret_cast<const char*>(&len), sizeof(len));
            out.write(s.data(), len);
        }
    }

    out.close();
    return true;
}

//bool DataManipulator::updateTuple(Relation* relation,
//                                  int rowIndex,
//                                  const std::vector<std::string>& newData)
//{
//    // 1) Validate inputs
//    const auto& attrs = relation->getCAttributes();
//    if ((int)newData.size() != (int)attrs.size()) {
//        std::cerr << "updateTuple: newData size mismatch with schema\n";
//        return false;
//    }
//
//    // 2) Prepare a vector of attribute names in iteration order
//    std::vector<std::string> names;
//    for (const auto &p : attrs) names.push_back(p.first);
//
//    // 3) For each column: read, modify, write back
//    const std::string baseDir = "../Databases/" + relation->getDatabaseName()
//                                + "/" + relation->getName() + "/";
//
//    for (size_t i = 0; i < names.size(); ++i) {
//        const std::string &col = names[i];
//        CAttribute* attr = attrs.at(col);
//        std::string path = baseDir + col + ".dat";
//
//        // Read existing values
//        std::vector<std::string> values;
//        if (!readColumnFile(path, attr->type, values)) return false;
//
//        if (rowIndex < 0 || rowIndex >= (int)values.size()) {
//            std::cerr << "updateTuple: rowIndex out of range for column " << col << "\n";
//            return false;
//        }
//
//        // Replace the target row’s value
//        values[rowIndex] = newData[i];
//
//        // Write all values back
//        if (!writeColumnFile(path, attr->type, values)) return false;
//    }
//
//    return true;
//}
//#include "../Engines/ConstraintValidator.hpp"

// Assumes 'row' represents a valid existing row to be updated
//bool DataManipulator::updateTuple(Relation* relation, Row* row) {
//    if (!relation || !row) {
//        throw std::invalid_argument("Relation or Row is null.");
//    }
//
//    const std::vector<ColVal*>& colvals = row->getColVals();
//    if (colvals.empty()) {
//        throw std::invalid_argument("Row has no ColVals.");
//    }
//
//    // Step 1: Validate constraints
//    for (ColVal* colval : colvals) {
//        if (!colval) continue; // Safety
//
//        CAttribute* attribute = colval->getAttribute();
//        if (!attribute) continue; // Safety
//
//        // Primary Key constraint check
//        if (attribute->isPK) {
//          		PrimaryKeyConstraint* pkConstraint;
//          		for (auto & pkConstraintiter : relation->getpks()) {
//						if (pkConstraintiter.second->getAttribute() == attribute) {
//            				pkConstraint = pkConstraintiter.second;
//            			}
//          		}
////            if (!ConstraintValidator::validatePrimaryKey(relation, *colval)) {
//            if (!ConstraintValidator::validatePrimaryKey(relation, *colval, pkConstraint)) {
//                std::cerr << "Primary key constraint violated for attribute: " << attribute->getName() << std::endl;
//                return false;
//            }
//        }
//
//        // Unique Key constraint check
//        if (attribute->isUnique && (attribute->isPK == false)) {
////            if (!ConstraintValidator::validateUniqueKey(relation, *colval)) {
//            UniqueKeyConstraint* ukConstraint;
//          		for (auto & ukConstraintiter : relation->getuks()) {
//						if (ukConstraintiter.second->getAttribute() == attribute) {
//            				ukConstraint = ukConstraintiter.second;
//            			}
//          		}
//            if (!ConstraintValidator::validateUniqueKey(relation, *colval, ukConstraint)){
//
//
//                std::cerr << "Unique key constraint violated for attribute: " << attribute->getName() << std::endl;
//                return false;
//            }
//        }
//
//        // Foreign Key constraint check
//        if (attribute->isFK) {
//          		ForeignKeyConstraint* fkConstraint;
//                        for (auto & fkConstraintiter : relation->getfks()) {
//                                if (fkConstraintiter.second->getChildColumn() == attribute) {
//                                        fkConstraint = fkConstraintiter.second;
//                                }
//                        }
//            if (!ConstraintValidator::validateForeignKey(*colval, fkConstraint)) {
//                // Check if the foreign key constraint is violated
//                std::cerr << "Foreign key constraint violated for attribute: " << attribute->getName() << std::endl;
//                return false;
//
//            }
//                std::cerr << "Foreign key constraint violated for attribute: " << attribute->getName() << std::endl;
//                return false;
//            }
//        }
//
//   // Step 2: Append update to the corresponding files
//for (int i = 0; i < colvals.size(); ++i) {
//    ColVal* colval = colvals[i];
//    if (!colval) continue;
//
//    CAttribute* attribute = colval->getAttribute();
//    if (!attribute) continue;
//
//    const std::string& filepath = colval->getPath();
//
//    // Open file in append mode
//    std::ofstream outfile(filepath, std::ios::app);
//    if (!outfile.is_open()) {
//        std::cerr << "Failed to open file for appending: " << filepath << std::endl;
//        return false;
//    }
//
//    // Decide what to write based on attribute type
//    if (colval->isNullValue()) {
//        outfile << "NULL" << std::endl;
//    } else {
//        std::string type = attribute->getType();
//        if (type == "int") {
//            outfile << colval->getIntValue() << std::endl;
//        } else if (type == "float") {
//            outfile << colval->getDoubleValue() << std::endl;
//        } else if (type == "string") {
//            outfile << colval->getStringValue() << std::endl;
//        }
////        else if (type == "date") {
////            Date_DDMMYYYY_Type date = colval->getDateValue();
////            outfile << date.toString() << std::endl;  // assuming Date_DDMMYYYY_Type has a toString() method
////        }
//        else {
//            std::cerr << "Unknown attribute type: " << type << std::endl;
//            return false;
//        }
//    }
//
//    outfile.close();
//    }
//
//    return true;
//}
//

//// DataManipulator.cpp with date
//bool DataManipulator::updateTuple(Relation* relation, Row* row) {
//    if (!relation || !row) {
//        std::cerr << "Error: Relation or Row is null." << std::endl;
//        return false;
//    }
//
//    const auto& colvals = row->getColVals();
//    if (colvals.empty()) {
//        std::cerr << "Error: Row has no ColVals." << std::endl;
//        return false;
//    }
//
//    // Step 1: Validate constraints
//    for (const auto& colval : colvals) {
//        if (!colval) continue;
//
//        CAttribute* attribute = colval->getAttribute();
//        if (!attribute) continue;
//
//        // Validate constraints (Primary Key, Unique Key, Foreign Key)
//        if (attribute->isPK) {
//            auto pkConstraint = relation->getpks().at(attribute->getName());
//            if (!ConstraintValidator::validatePrimaryKey(relation, *colval, pkConstraint)) {
//                std::cerr << "Primary key constraint violated for attribute: " << attribute->getName() << std::endl;
//                return false;
//            }
//        }
//        if (attribute->isUnique && !attribute->isPK) {
//            auto ukConstraint = relation->getuks().at(attribute->getName());
//            if (!ConstraintValidator::validateUniqueKey(relation, *colval, ukConstraint)) {
//                std::cerr << "Unique key constraint violated for attribute: " << attribute->getName() << std::endl;
//                return false;
//            }
//        }
//        if (attribute->isFK) {
//            auto fkConstraint = relation->getfks().at(attribute->getName());
//            if (!ConstraintValidator::validateForeignKey(*colval, fkConstraint)) {
//                std::cerr << "Foreign key constraint violated for attribute: " << attribute->getName() << std::endl;
//                return false;
//            }
//        }
//    }
//
//    // Step 2: Update files
//    for (const auto& colval : colvals) {
//        if (!colval) continue;
//
//        CAttribute* attribute = colval->getAttribute();
//        if (!attribute) continue;
//
//        std::string filepath = colval->getPath();
//        std::vector<std::string> values;
//
//        // Read existing values
//        if (!readColumnFile(filepath, attribute->getType(), values)) {
//            std::cerr << "Error reading column file: " << filepath << std::endl;
//            return false;
//        }
//
//        // Update the specific row
//        int rowIndex = row->getRelation()->getNumRows() - 1; // Assuming last row is updated
//        if (rowIndex < 0 || rowIndex >= (int)values.size()) {
//            std::cerr << "Error: Row index out of range for column: " << attribute->getName() << std::endl;
//            return false;
//        }
//        values[rowIndex] = colval->getStringValue();
//
//        // Write updated values back
//        if (!writeColumnFile(filepath, attribute->getType(), values)) {
//            std::cerr << "Error writing column file: " << filepath << std::endl;
//            return false;
//        }
//    }
//
//    return true;
//}





bool DataManipulator::updateTuple(Relation* relation, Row* row) {
    if (!relation || !row) {
        std::cerr << "Error: Relation or Row is null." << std::endl;
        return false;
    }

    const auto& colvals = row->getColVals();
    if (colvals.empty()) {
        std::cerr << "Error: Row has no ColVals." << std::endl;
        return false;
    }

    for (const auto& pcolval : colvals) {
        ColVal* colval = pcolval.second;
        if (!colval) continue;

        CAttribute* attribute = colval->getAttribute();
        if (!attribute) continue;

        // Validate Primary Key
        if (attribute->isPK) {
            auto pkIt = relation->getpks().find(attribute->getName());
            if (pkIt == relation->getpks().end()) {
                std::cerr << "Error: Primary key constraint not found for attribute: " << attribute->getName() << std::endl;
                return false;
            }
            if (!ConstraintValidator::validatePrimaryKey(relation, *colval, pkIt->second)) {
                std::cerr << "Primary key constraint violated for attribute: " << attribute->getName() << std::endl;
                return false;
            }
        }

        // Validate Unique Key
        if (attribute->isUnique && !attribute->isPK) {
            auto ukIt = relation->getuks().find(attribute->getName());
            if (ukIt == relation->getuks().end()) {
                std::cerr << "Error: Unique key constraint not found for attribute: " << attribute->getName() << std::endl;
                return false;
            }
            if (!ConstraintValidator::validateUniqueKey(relation, *colval, ukIt->second)) {
                std::cerr << "Unique key constraint violated for attribute: " << attribute->getName() << std::endl;
                return false;
            }
        }

        // Validate Foreign Key
        if (attribute->isFK) {
            auto fkIt = relation->getfks().find(attribute->getName());
            if (fkIt == relation->getfks().end()) {
                std::cerr << "Error: Foreign key constraint not found for attribute: " << attribute->getName() << std::endl;
                return false;
            }
            if (!ConstraintValidator::validateForeignKey(*(colval), fkIt->second)) {
                std::cerr << "Foreign key constraint violated for attribute: " << attribute->getName() << std::endl;
                return false;
            }
        }
    }
    // Proceed with updating files...
    // Step 2: Update files
    for (const auto& pcolval : colvals) {
        ColVal* colval = pcolval.second;
        if (!colval) continue;

        CAttribute* attribute = colval->getAttribute();
        if (!attribute) continue;

        std::string filepath = colval->getPath();
        std::vector<std::string> values;

        // Read existing values
        if (!readColumnFile(filepath, attribute->getType(), values)) {
            std::cerr << "Error reading column file: " << filepath << std::endl;
            return false;
        }

        // Update the specific row
        int rowIndex = row->getRelation()->getNumRows() - 1; // Assuming last row is updated
        if (rowIndex < 0 || rowIndex >= (int)values.size()) {
            std::cerr << "Error: Row index out of range for column: " << attribute->getName() << std::endl;
            return false;
        }
        values[rowIndex] = colval->getStringValue();

        // Write updated values back
        if (!writeColumnFile(filepath, attribute->getType(), values)) {
            std::cerr << "Error writing column file: " << filepath << std::endl;
            return false;
        }
    }
    return true;
}