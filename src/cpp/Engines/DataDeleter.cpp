//
// Created by Pradyun Devarakonda on 12/03/25.
//
#include "DataDeleter.h"
#include <fstream>
#include <iostream>
#include <vector>

//bool DataDeleter::deleteByPK(Relation* relation, const ColVal& pkValue) {
//    if (!relation || !pkValue.getAttribute()) {
//        return false;
//    }
//
//    // Get the primary key attribute
//    CAttribute* pkAttr = relation->getPrimaryKey().attribute;
//    if (!pkAttr) {
//        std::cerr << "No primary key defined for relation " << relation->getName() << std::endl;
//        return false;
//    }
//
//    // Read all values except the one to delete
//    std::string path = "../Databases/" + relation->getDBName() + "/" +
//                      relation->getName() + "/" + pkAttr->getName() + ".dat";
//
//    std::vector<ColVal> remainingValues;
//    std::ifstream in(path, std::ios::binary);
//    if (!in.is_open()) {
//        std::cerr << "Failed to open file: " << path << std::endl;
//        return false;
//    }
//
//    // Read and store all values except the one to delete
//    size_t deleteIndex = (size_t)-1;
//    size_t currentIndex = 0;
//
//    while (true) {
//        ColVal currentValue(pkAttr);
//
//        if (pkAttr->type == "integer") {
//            int64_t v;
//            if (!in.read(reinterpret_cast<char*>(&v), sizeof(v))) break;
//            currentValue = ColVal(pkAttr, static_cast<int>(v));
//        }
//        else if (pkAttr->type == "float") {
//            double d;
//            if (!in.read(reinterpret_cast<char*>(&d), sizeof(d))) break;
//            currentValue = ColVal(pkAttr, d);
//        }
//        // Add other type handling as needed
//
//        if (currentValue == pkValue) {
//            deleteIndex = currentIndex;
//        } else {
//            remainingValues.push_back(currentValue);
//        }
//        currentIndex++;
//    }
//    in.close();
//
//    if (deleteIndex == (size_t)-1) {
//        std::cerr << "Value not found in primary key column" << std::endl;
//        return false;
//    }
//
//    // Rewrite the file without the deleted value
//    std::ofstream out(path, std::ios::binary | std::ios::trunc);
//    if (!out.is_open()) {
//        std::cerr << "Failed to open file for writing: " << path << std::endl;
//        return false;
//    }
//
//    for (const auto& val : remainingValues) {
//        if (pkAttr->type == "integer") {
//            int64_t v = val.getIntValue();
//            out.write(reinterpret_cast<const char*>(&v), sizeof(v));
//        }
//        else if (pkAttr->type == "float") {
//            double d = val.getDoubleValue();
//            out.write(reinterpret_cast<const char*>(&d), sizeof(d));
//        }
//        // Add other type handling as needed
//    }
//    out.close();
//
//    // Delete corresponding values from other columns
//    for (const auto& pair : relation->getCAttributes()) {
//        if (pair.second == pkAttr) continue;
//
//        std::string colPath = "../Databases/" + relation->getDBName() + "/" +
//                             relation->getName() + "/" + pair.second->getName() + ".dat";
//
//        // Implement similar read/write logic for other columns
//        // Make sure to skip the value at deleteIndex
//    }
//
//    return true;
//}

//DELETE EACH row by PK {SOFT DELETE}

bool DataDeleter::deleteRow(Relation* relation, const std::vector<std::string>& primaryKeyValues) {
    if (!relation) {
        std::cerr << "Relation is null." << std::endl;
        return false;
    }

    // Get the primary key attributes
    auto primaryKey = relation->getPrimaryKey();
    if (primaryKey.attributeRefs.size() != primaryKeyValues.size()) {
        std::cerr << "Primary key values do not match the primary key definition." << std::endl;
        return false;
    }

    // Iterate over each primary key attribute
    for (size_t i = 0; i < primaryKey.attributeRefs.size(); ++i) {
        const std::string& attrName = primaryKey.attributeRefs[i];
        const std::string& value = primaryKeyValues[i];

        // Get the attribute
        CAttribute* attribute = relation->getCAttribute(attrName);
        if (!attribute) {
            std::cerr << "Attribute " << attrName << " not found in relation." << std::endl;
            return false;
        }

        // Open the corresponding .dat file
        std::string filePath = "../Databases/" + relation->getDatabaseName() + "/" + relation->getName() + "/" + attribute->getName() + ".dat";
        std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return false;
        }

        // Search for the row with the matching primary key value
        std::string line;
        size_t rowIndex = 0;
        bool found = false;
        while (std::getline(file, line)) {
            if (line.find(value) != std::string::npos) { // Simplified matching
                found = true;
                break;
            }
            ++rowIndex;
        }

        if (!found) {
            std::cerr << "Row with primary key value " << value << " not found." << std::endl;
            return false;
        }

        // Mark the row as deleted by setting the isDeleted flag
        file.seekp(rowIndex * sizeof(uint8_t), std::ios::beg); // Assuming isDeleted is at the start
        uint8_t isDeleted = 1;
        file.write(reinterpret_cast<char*>(&isDeleted), sizeof(isDeleted));
        file.close();
    }

    return true;
}

bool DataDeleter::deleteByPK(Relation* relation, const ColVal& pkValue) {
    if (!relation || !pkValue.getAttribute()) {
        return false;
    }

    // Get the primary key attribute
    CAttribute* pkAttr = relation->getPrimaryKey().attribute;
    if (!pkAttr) {
        std::cerr << "No primary key defined for relation " << relation->getName() << std::endl;
        return false;
    }

    // Prepare base path for all columns
    std::string basePath = "../Databases/" + relation->getDBName() + "/"
                         + relation->getName() + "/";

    // Find the index of the row to delete
    std::string pkPath = basePath + pkAttr->getName() + ".dat";
    size_t deleteIndex = (size_t)-1;
    size_t currentIndex = 0;

    // Scan PK column to find deletion index
    std::ifstream pkIn(pkPath, std::ios::binary);
    if (!pkIn.is_open()) {
        std::cerr << "Failed to open PK file: " << pkPath << std::endl;
        return false;
    }

    while (true) {
        ColVal currentValue(pkAttr);
        bool readSuccess = false;

        if (pkAttr->type == "integer") {
            int64_t v;
            if (pkIn.read(reinterpret_cast<char*>(&v), sizeof(v))) {
                currentValue = ColVal(pkAttr, static_cast<int>(v));
                readSuccess = true;
            }
        }
        else if (pkAttr->type == "decimal") {
            double d;
            if (pkIn.read(reinterpret_cast<char*>(&d), sizeof(d))) {
                currentValue = ColVal(pkAttr, d);
                readSuccess = true;
            }
        }
        else if (pkAttr->type == "string") {
            uint16_t len;
            if (pkIn.read(reinterpret_cast<char*>(&len), sizeof(len))) {
                std::string str(len, '\0');
                if (pkIn.read(&str[0], len)) {
                    currentValue = ColVal(pkAttr, str);
                    readSuccess = true;
                }
            }
        }

        if (!readSuccess) break;

        if (currentValue == pkValue) {
            deleteIndex = currentIndex;
            break;  // Found match, stop scanning
        }
        currentIndex++;
    }
    pkIn.close();

    if (deleteIndex == (size_t)-1) {
        std::cerr << "PK value not found in relation " << relation->getName() << std::endl;
        return false;
    }

    // Process all columns
    for (const auto& [attrName, attribute] : relation->getCAttributes()) {
        std::string colPath = basePath + attribute->getName() + ".dat";

        // Read all values except the deleted index
        std::vector<ColVal> columnValues;
        std::ifstream colIn(colPath, std::ios::binary);
        if (!colIn.is_open()) {
            std::cerr << "Failed to open column file: " << colPath << std::endl;
            return false;
        }

        while (true) {
            ColVal val(attribute);
            bool readSuccess = false;

            if (attribute->type == "integer") {
                int64_t v;
                if (colIn.read(reinterpret_cast<char*>(&v), sizeof(v))) {
                    val = ColVal(attribute, static_cast<int>(v));
                    readSuccess = true;
                }
            }
            else if (attribute->type == "decimal") {
                double d;
                if (colIn.read(reinterpret_cast<char*>(&d), sizeof(d))) {
                    val = ColVal(attribute, d);
                    readSuccess = true;
                }
            }
            else if (attribute->type == "string") {
                uint16_t len;
                if (colIn.read(reinterpret_cast<char*>(&len), sizeof(len))) {
                    std::string str(len, '\0');
                    if (colIn.read(&str[0], len)) {
                        val = ColVal(attribute, str);
                        readSuccess = true;
                    }
                }
            }

            if (!readSuccess) break;
            columnValues.push_back(val);
        }
        colIn.close();

        // Rewrite file skipping deleted index
        std::ofstream colOut(colPath, std::ios::binary | std::ios::trunc);
        if (!colOut.is_open()) {
            std::cerr << "Failed to rewrite column file: " << colPath << std::endl;
            return false;
        }

        for (size_t i = 0; i < columnValues.size(); ++i) {
            if (i == deleteIndex) continue;

            const ColVal& val = columnValues[i];
            if (attribute->type == "integer") {
                int64_t v = val.getIntValue();
                colOut.write(reinterpret_cast<const char*>(&v), sizeof(v));
            }
            else if (attribute->type == "decimal") {
                double d = val.getDoubleValue();
                colOut.write(reinterpret_cast<const char*>(&d), sizeof(d));
            }
            else if (attribute->type == "string") {
                const std::string& str = val.getStringValue();
                uint16_t len = str.size();
                colOut.write(reinterpret_cast<const char*>(&len), sizeof(len));
                colOut.write(str.c_str(), len);
            }
        }
        colOut.close();
    }

    return true;
}

bool DataDeleter::deleteRow(Relation* relation, Row* row) {
    if (!relation || !row) return false;

    // Get the primary key value from the row
    CAttribute* pkAttr = relation->getPrimaryKey().attribute;
    if (!pkAttr) return false;

    ColVal* pkValue = nullptr;
    for (ColVal* val : row->getColVals()) {
        if (val->getAttribute() == pkAttr) {
            pkValue = val;
            break;
        }
    }

    if (!pkValue) return false;
    return deleteByPK(relation, *pkValue);
}

bool DataDeleter::markRowDeleted(Relation* relation, Row* row) {
    // Implementation for soft delete - could add a deleted flag column
    // Not implemented in this version
    return false;
}

bool DataDeleter::purgeDeletedRows(Relation* relation) {
    // Implementation for cleaning up soft-deleted rows
    // Not implemented in this version
    return false;
}