////
//// Created by Pradyun Devarakonda on 12/03/25.
////
//
//#include "DataLoader.h"
//
//
////bool DMLEngine::loadDatafromCSV(const & Database, const string & CSVfile, const string & RelationName){
//    // Load data from CSV file into the specified relation in the specified database.
//    // The CSV file should have a header row with the attribute names.
//    // The order of the attributes in the CSV file should match the order of the attributes in the relation.
//    // The CSV file should have one row for each tuple in the relation.
//    // The CSV file should be comma-separated.
//    // The CSV file should not have any quotes around the attribute values.
//    // The CSV file should not have any empty lines.
//    // The CSV file should not have any empty values.
//    // The CSV file should not have any duplicate tuples.
//    // The CSV file should not have any tuples that violate the primary key constraint.
//    // The CSV file should not have any tuples that violate the foreign key constraint.
//    // The CSV file should not have any tuples that violate the check constraint.
//    // The CSV file should not have any tuples that violate the unique constraint.
//    // The CSV file should not have any tuples that violate the not null constraint.
//    // The CSV file should not have any tuples that violate the default constraint.
//    // The CSV file should not have any tuples that violate the data type constraint.
//    // The CSV file should not have any tuples that violate the domain constraint.
//    // The CSV file should not have any tuples that violate the cardinality constraint.
//    // The CSV file should not have any tuples that violate the referential integrity constraint.
//    // The CSV file should not have any tuples that violate the entity integrity constraint.
//    // The CSV file should not have any tuples that violate the user-defined constraint.
//    // The CSV file should not have any tuples that violate the null constraint.
//    // The CSV file should not have any tuples that violate the key constraint.
//    // The CSV file should not have any tuples that violate the integrity constraint.
//    // The CSV file should not have any tuples that violate the constraint.
//    // The CSV file should not have any tuples that violate the schema constraint.
//    // The CSV file should not have any tuples that violate the table constraint.
//    // The CSV file should not have any tuples that violate the view constraint.
//    // The CSV file should not have any tuples that violate the index constraint.
//    // The CSV file should not have any tuples that violate the trigger constraint.
//    // The CSV file should not have any tuples that violate the security constraint.
//    // The CSV file should not have any tuples that violate the authorization constraint.
//    // The CSV file should not have any tuples that violate the access constraint.
//
////bool DataLoader::loadDataFromCSV(Database* db, const std::string& CSVfile, const std::string& relationName) {
////    std::ifstream file(CSVfile);
////    if (!file.is_open()) {
////        std::cerr << "Error: Unable to open CSV file " << CSVfile << std::endl;
////        return false;
////    }
////
////    std::stringstream buffer;
////    buffer << file.rdbuf();
////    std::string fileContent = buffer.str();
////
////    Tbl::Table table(fileContent);
////    if (!table.isValid()) { // Ensure Table is valid
////        std::cerr << "Error: Failed to parse CSV data." << std::endl;
////        return false;
////    }
////
////    Relation* relation = db.getRelation(relationName);
////    if (!relation) {
////        std::cerr << "Error: Relation " << relationName << " not found in database." << std::endl;
////        return false;
////    }
////
////    const auto &dbName = db.getName();
////    const auto& attributes = relation->getCAttributes();
////
////    if (table.NumCols() != attributes.size()) {
////        std::cerr << "Error: CSV columns do not match the relation schema." << std::endl;
////        return false;
////    }
////
////    std::unordered_map<std::string, std::ofstream> columnFiles;
////    for (const auto& pair : attributes) {
////        auto& attr = pair.second;
////        std::string columnFilePath = "../Databases/" + dbName + "/" + relationName + "/" + attr->name + ".dat";
////
////        std::ofstream& outFile = columnFiles[attr->name];
////        outFile.open(columnFilePath, std::ios::app | std::ios::binary);
////        if (!outFile.is_open()) {
////            std::cerr << "Error: Unable to open column file " << columnFilePath << std::endl;
////
////            // Close previously opened files
////            for (auto& pair : columnFiles) {
////                if (pair.second.is_open()) pair.second.close();
////            }
////            return false;
////        }
////    }
////
////    // Iterate over each row
////    for (size_t row = 0; row < table.NumRows(); ++row) {
////        size_t colIndex = 0;  // Reset column index for each row
////
////        for (const auto& pair : attributes) {
////            const auto& attr = pair.second;
////            std::ofstream& outFile = columnFiles[attr->name];
////
////            try {
////                if (attr->type == "int") {
////                    int value = table.GetInt(row, colIndex);
////                    outFile.write(reinterpret_cast<const char*>(&value), sizeof(int));
////                } else if (attr->type == "float") {
////                    float value = static_cast<float>(table.GetDouble(row, colIndex));
////                    outFile.write(reinterpret_cast<const char*>(&value), sizeof(float));
////                } else if (attr->type == "Date_DDMMYYYY_Type") {
////                    // Date_DDMMYYYY_Type date = Date_DDMMYYYY_Type::parse(table.GetString(row, colIndex));
////                    // std::string binaryDate = date.toBinary(); // Ensure a proper serialization method
////                    // outFile.write(binaryDate.data(), binaryDate.size());
////                    Date_DDMMYYYY_Type date = Date_DDMMYYYY_Type::parse(table.GetString(row, colIndex));
////                    outFile.write(reinterpret_cast<const char*>(&date), sizeof(Date_DDMMYYYY_Type));
////                } else {
////                    std::string value = table.GetString(row, colIndex);
////                    size_t len = value.size();
////                    outFile.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
////                    outFile.write(value.c_str(), len);
////                }
////            } catch (const std::exception& e) {
////                std::cerr << "Error processing column " << attr->name << " in row " << row << ": " << e.what() << std::endl;
////
////                // Cleanup before returning
////                for (auto& pair : columnFiles) {
////                    pair.second.close();
////                }
////                return false;
////            }
////
////            colIndex++;
////        }
////    }
////
////    // Close all files
////    for (auto& pair : columnFiles) {
////        pair.second.close();
////    }
////
////    return true;
////}
//bool DataLoader::loadDataFromCSV(Database* db, const std::string& CSVfile, const std::string& relationName) {
//    std::ifstream file(CSVfile);
//    if (!file.is_open()) {
//        std::cerr << "Error: Unable to open CSV file " << CSVfile << std::endl;
//        return false;
//    }
//
//    std::stringstream buffer;
//    buffer << file.rdbuf();
//    file.close();
//
//    Tbl::Table table(buffer.str());
//    if (!table) { // Check if table was successfully parsed
//        std::cerr << "Error: Failed to parse CSV data." << std::endl;
//        return false;
//    }
//
//    Relation* relation = db->getRelation(relationName);
//    if (!relation) {
//        std::cerr << "Error: Relation " << relationName << " not found in database." << std::endl;
//        return false;
//    }
//
//    const auto& dbName = db->getName();
//    const auto& attributes = relation->getCAttributes();
//
//    if (table.GetNumColumns() != attributes.size()) {
//        std::cerr << "Error: CSV columns do not match the relation schema." << std::endl;
//        return false;
//    }
//
//    std::unordered_map<std::string, std::ofstream> columnFiles;
//    for (const auto& pair : attributes) {
//        auto& attr = pair.second;
//        std::string columnFilePath = "../Databases/" + dbName + "/" + relationName + "/" + attr->name + ".dat";
//
//        std::ofstream& outFile = columnFiles[attr->name];
//        outFile.open(columnFilePath, std::ios::app | std::ios::binary);
//        if (!outFile.is_open()) {
//            std::cerr << "Error: Unable to open column file " << columnFilePath << std::endl;
//            for (auto& pair : columnFiles) {
//                if (pair.second.is_open()) pair.second.close();
//            }
//            return false;
//        }
//    }
//
//    for (size_t row = 0; row < table.GetNumRows(); ++row) {
//        size_t colIndex = 0;
//        for (const auto& pair : attributes) {
//            const auto& attr = pair.second;
//            std::ofstream& outFile = columnFiles[attr->name];
//
//            try {
//                if (attr->type == "int") {
////                    int value = table.Get<int>(row, colIndex);
//                    int64_t value = table.Get<int64_t>(row, colIndex);
//                    outFile.write(reinterpret_cast<const char*>(&value), sizeof(int));
//                } else if (attr->type == "float") {
//                    float value = static_cast<float>(table.Get<double>(row, colIndex));
//                    outFile.write(reinterpret_cast<const char*>(&value), sizeof(float));
//                } else if (attr->type == "Date_DDMMYYYY_Type") {
//                    std::string dateStr = table.Get<std::string>(row, colIndex);
//                    Date_DDMMYYYY_Type date = Date_DDMMYYYY_Type::parse(dateStr);
//                    outFile.write(reinterpret_cast<const char*>(&date), sizeof(Date_DDMMYYYY_Type));
//                } else {
//                    std::string value = table.Get<std::string>(row, colIndex);
//                    size_t len = value.size();
//                    outFile.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
//                    outFile.write(value.c_str(), len);
//                }
//            } catch (const std::exception& e) {
//                std::cerr << "Error processing column " << attr->name << " in row " << row << ": " << e.what() << std::endl;
//                for (auto& pair : columnFiles) {
//                    pair.second.close();
//                }
//                return false;
//            }
//
//            colIndex++;
//        }
//    }
//
//    for (auto& pair : columnFiles) {
//        pair.second.close();
//    }
//
//    return true;
//}
#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <algorithm>

// Include the Tbl header (make sure your include paths are set correctly)
#include "../include/Tbl.hpp"

// Helper functions – you need to implement these in your project:
std::unordered_set<std::string> getReferencedKeySet(Database* db, ForeignKeyConstraint* fk) {
    std::unordered_set<std::string> refSet;

    std::string dbName = db->getName();
    std::string parentRel = fk->parentTable->getName();
    std::string parentAttr = fk->parentColumn->name;

    Relation* parentRelation = db->getRelation(parentRel);
    if (!parentRelation) {
        std::cerr << "Error: Parent relation " << parentRel << " not found.\n";
        return refSet;
    }

    const auto& attributes = parentRelation->getCAttributes();
    if (attributes.find(parentAttr) == attributes.end()) {
        std::cerr << "Error: Attribute " << parentAttr << " not found in parent relation.\n";
        return refSet;
    }

    CAttribute* attr = attributes.at(parentAttr);
    std::string filePath = "../Databases/" + dbName + "/" + parentRel + "/" + parentAttr + ".dat";

    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << "\n";
        return refSet;
    }

    if (attr->type == "int") {
        int64_t val;
        while (inFile.read(reinterpret_cast<char*>(&val), sizeof(int64_t))) {
            refSet.insert(std::to_string(val));
        }
    } else if (attr->type == "float") {
        double val;
        while (inFile.read(reinterpret_cast<char*>(&val), sizeof(double))) {
            refSet.insert(std::to_string(val));
        }
    } else if (attr->type == "Date_DDMMYYYY_Type") {
        Date_DDMMYYYY_Type date;
        while (inFile.read(reinterpret_cast<char*>(&date), sizeof(Date_DDMMYYYY_Type))) {
            refSet.insert(Date_DDMMYYYY_Type::dateToString(date));
        }
    } else { // assume string
        while (true) {
            size_t len;
            if (!inFile.read(reinterpret_cast<char*>(&len), sizeof(size_t))) break;
            std::string val(len, '\0');
            if (!inFile.read(&val[0], len)) break;
            refSet.insert(val);
        }
    }

    inFile.close();
    return refSet;
}

bool DataLoader::loadDataFromCSV(Database* db, const std::string& relationName, const std::string& csvPath) {
    Relation* relation = db->getRelation(relationName);
    if (!relation) {
        std::cerr << "Relation " << relationName << " not found.\n";
        return false;
    }

    std::ifstream csvFile(csvPath);
    if (!csvFile.is_open()) {
        std::cerr << "Failed to open CSV file: " << csvPath << "\n";
        return false;
    }

    const auto& attributes = relation->getCAttributes();
    std::vector<std::string> attributeNames;
    for (const auto& [name, _] : attributes) {
        attributeNames.push_back(name);
    }

    // Constraint tracking sets
    std::unordered_map<std::string, std::unordered_set<std::string>> pkSets;
    std::unordered_map<std::string, std::unordered_set<std::string>> ukSets;
    std::unordered_map<std::string, std::unordered_set<std::string>> fkSets;

    for (const auto& [attrName, pk] : relation->pks) {
        pkSets[attrName] = {};
    }

    for (const auto& [attrName, uk] : relation->uks) {
        ukSets[attrName] = {};
    }

    for (const auto& [attrName, fk] : relation->fks) {
        fkSets[attrName] = getReferencedKeySet(db, fk);
    }

    // Open output streams
    std::unordered_map<std::string, std::ofstream> outStreams;
    std::string basePath = "../Databases/" + db->getName() + "/" + relationName + "/";
    for (const auto& name : attributeNames) {
        outStreams[name].open(basePath + name + ".dat", std::ios::binary | std::ios::app);
        if (!outStreams[name]) {
            std::cerr << "Error opening file for writing: " << name << "\n";
            return false;
        }
    }

    std::string line;
    while (getline(csvFile, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (row.size() != attributeNames.size()) {
            std::cerr << "Invalid row (column count mismatch): " << line << "\n";
            return false;
        }

        for (size_t i = 0; i < row.size(); ++i) {
            const std::string& attrName = attributeNames[i];
            const std::string& value = row[i];
            const CAttribute* attr = attributes.at(attrName);

            // Primary Key
            if (pkSets.count(attrName)) {
                if (!pkSets[attrName].insert(value).second) {
                    std::cerr << "Primary Key violation on " << attrName << ": " << value << "\n";
                    return false;
                }
            }

            // Unique Key
            if (ukSets.count(attrName)) {
                if (!ukSets[attrName].insert(value).second) {
                    std::cerr << "Unique Key violation on " << attrName << ": " << value << "\n";
                    return false;
                }
            }

            // Foreign Key
            if (fkSets.count(attrName)) {
                if (fkSets[attrName].find(value) != fkSets[attrName].end()) {
                    std::cerr << "Foreign Key violation on " << attrName << ": " << value << "\n";
                    return false;
                }
            }

            // Write to disk
            if (attr->type == "int") {
                int64_t val = std::stoll(value);
                outStreams[attrName].write(reinterpret_cast<char*>(&val), sizeof(int64_t));
            } else if (attr->type == "float") {
                double val = std::stod(value);
                outStreams[attrName].write(reinterpret_cast<char*>(&val), sizeof(double));
            }
//            else if (attr->type == "Date_DDMMYYYY_Type") {
//                Date_DDMMYYYY_Type d = Date_DDMMYYYY_Type::parse(value);
//                outStreams[attrName].write(reinterpret_cast<char*>(&d), sizeof(Date_DDMMYYYY_Type));
//            }
            else {
                size_t len = value.length();
                outStreams[attrName].write(reinterpret_cast<char*>(&len), sizeof(size_t));
                outStreams[attrName].write(value.c_str(), len);
            }
        }
    }

    for (auto& [_, out] : outStreams) {
        out.close();
    }

    csvFile.close();
    std::cout << "Data successfully loaded into relation: " << relationName << "\n";
    return true;
}


//---

//### **Notes:**
//- **In-Memory Constraint Checks:**
//  For each row loaded from CSV, the code converts each field into a string (using `std::to_string` for numbers, and a helper conversion for dates) to compare values. For primary key or unique columns, it checks against an in‑memory `unordered_set` (per attribute) to catch duplicates.
//- **Foreign Key Checks:**
//  For each attribute that is a foreign key (as indicated by its presence in the `fkLookup` map), the value is checked against a pre‑loaded set of valid parent keys.
//- **Writing Data:**
//  Values are written to the appropriate column file using binary writes—numeric types as fixed‑size data, and strings with a length prefix.
//- **Error Handling:**
//  If any constraint is violated, an error message is printed and the function returns `false`.
//
//This version 0.0 demonstrates one approach to loading CSV data while enforcing integrity constraints without loading entire columns into memory. In a production system you’d likely optimize the in‑memory structures (or use a disk‑based index if the data is too large) and add robust error recovery/transaction support.
//

                //std::string dateToString(const Date_DDMMYYYY_Type& date) {
                //    // Convert date values to a normalized string, e.g., YYYY-MM-DD.
                //    char buffer[11];  // YYYY-MM-DD + ull terminator
                //    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", date.year, date.month, date.day);
                //    return std::string(buffer);
                //}
                //