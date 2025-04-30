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
#include "DataDeleter.h"
#include <filesystem>
#include <fstream>
#include <iostream>
namespace fs = std::filesystem;

bool DataDeleter::deleteRow(Relation* relation, const ColVal& pkVal) {

    // 1) find the PK attribute & its index within getCAttributes()
    const auto &attrs = relation->getCAttributes();
    CAttribute* pkAttr = nullptr;
    size_t colIndex = 0;
    for (auto const& [name, attr] : attrs) {
        if (attr->isPK) {
            pkAttr = attr;
            break;
        }
        ++colIndex;
    }
    if (!pkAttr) {
        std::cerr << "[DataDeleter] No PK on relation "
                  << relation->getName() << "\n";
        return false;
    }

    // 2) open the PK column file, scan for the matching pkVal, note its row offset
    std::string base = "../../Databases/" + relation->getName() + "/";
    fs::path pkPath = base + pkAttr->name + ".dat";
    std::fstream pkStream(pkPath, std::ios::in|std::ios::out|std::ios::binary);
    if (!pkStream) {
        std::cerr << "[DataDeleter] Cannot open " << pkPath << "\n";
        return false;
    }

    // skip header (row count)
//    pkStream.seekg(sizeof(int64_t), std::ios::beg);

    // each record is: uint8_t isDeleted + payload
    // find matching row number
    size_t targetRow = SIZE_MAX;
    for (size_t r=0; ; ++r) {
        uint8_t isDel;
        // read isDeleted
        if (!pkStream.read(reinterpret_cast<char*>(&isDel), sizeof(isDel)))
            break;
        // read int64_t key
        int64_t key;
        pkStream.read(reinterpret_cast<char*>(&key), sizeof(key));
        ColVal candidate(pkAttr, static_cast<int>(key));
        if (candidate == pkVal && isDel==0) {
            targetRow = r;
            break;
        }
    }
    if (targetRow==SIZE_MAX) {
        std::cerr << "[DataDeleter] PK value not found or already deleted.\n";
        return false;
    }

    // 3) for every column, jump to its row’s isDeleted byte, set =1
    for (auto const& [name, attr] : attrs) {
        fs::path colPath = base + name + ".dat";
        std::fstream colStream(colPath, std::ios::in|std::ios::out|std::ios::binary);
        if (!colStream) {
            std::cerr << "[DataDeleter] Cannot open " << colPath << "\n";
            return false;
        }
        // skip header
        std::streamoff offset = targetRow * (1 /*flag*/
                               + /*payload size*/ (
                                     attr->type=="integer" ? sizeof(int64_t)
                                   : attr->type=="decimal" ? sizeof(double)
                                   : /*string: len+data: unknown fixed? you'd need length-prefix + data; but batting average here: we can skip flag only */
                                     0
                               )
                             );
        colStream.seekp(offset, std::ios::beg);
        uint8_t one = 1;
        colStream.write(reinterpret_cast<char*>(&one), sizeof(one));
    }

    return true;
}



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
//    // Prepare base path for all columns
//    std::string basePath = "../Databases/" + relation->getDBName() + "/"
//                         + relation->getName() + "/";
//
//    // Find the index of the row to delete
//    std::string pkPath = basePath + pkAttr->getName() + ".dat";
//    size_t deleteIndex = (size_t)-1;
//    size_t currentIndex = 0;
//
//    // Scan PK column to find deletion index
//    std::ifstream pkIn(pkPath, std::ios::binary);
//    if (!pkIn.is_open()) {
//        std::cerr << "Failed to open PK file: " << pkPath << std::endl;
//        return false;
//    }
//
//    while (true) {
//        ColVal currentValue(pkAttr);
//        bool readSuccess = false;
//
//        if (pkAttr->type == "integer") {
//            int64_t v;
//            if (pkIn.read(reinterpret_cast<char*>(&v), sizeof(v))) {
//                currentValue = ColVal(pkAttr, static_cast<int>(v));
//                readSuccess = true;
//            }
//        }
//        else if (pkAttr->type == "decimal") {
//            double d;
//            if (pkIn.read(reinterpret_cast<char*>(&d), sizeof(d))) {
//                currentValue = ColVal(pkAttr, d);
//                readSuccess = true;
//            }
//        }
//        else if (pkAttr->type == "string") {
//            uint16_t len;
//            if (pkIn.read(reinterpret_cast<char*>(&len), sizeof(len))) {
//                std::string str(len, '\0');
//                if (pkIn.read(&str[0], len)) {
//                    currentValue = ColVal(pkAttr, str);
//                    readSuccess = true;
//                }
//            }
//        }
//
//        if (!readSuccess) break;
//
//        if (currentValue == pkValue) {
//            deleteIndex = currentIndex;
//            break;  // Found match, stop scanning
//        }
//        currentIndex++;
//    }
//    pkIn.close();
//
//    if (deleteIndex == (size_t)-1) {
//        std::cerr << "PK value not found in relation " << relation->getName() << std::endl;
//        return false;
//    }
//
//    // Process all columns
//    for (const auto& [attrName, attribute] : relation->getCAttributes()) {
//        std::string colPath = basePath + attribute->getName() + ".dat";
//
//        // Read all values except the deleted index
//        std::vector<ColVal> columnValues;
//        std::ifstream colIn(colPath, std::ios::binary);
//        if (!colIn.is_open()) {
//            std::cerr << "Failed to open column file: " << colPath << std::endl;
//            return false;
//        }
//
//        while (true) {
//            ColVal val(attribute);
//            bool readSuccess = false;
//
//            if (attribute->type == "integer") {
//                int64_t v;
//                if (colIn.read(reinterpret_cast<char*>(&v), sizeof(v))) {
//                    val = ColVal(attribute, static_cast<int>(v));
//                    readSuccess = true;
//                }
//            }
//            else if (attribute->type == "decimal") {
//                double d;
//                if (colIn.read(reinterpret_cast<char*>(&d), sizeof(d))) {
//                    val = ColVal(attribute, d);
//                    readSuccess = true;
//                }
//            }
//            else if (attribute->type == "string") {
//                uint16_t len;
//                if (colIn.read(reinterpret_cast<char*>(&len), sizeof(len))) {
//                    std::string str(len, '\0');
//                    if (colIn.read(&str[0], len)) {
//                        val = ColVal(attribute, str);
//                        readSuccess = true;
//                    }
//                }
//            }
//
//            if (!readSuccess) break;
//            columnValues.push_back(val);
//        }
//        colIn.close();
//
//        // Rewrite file skipping deleted index
//        std::ofstream colOut(colPath, std::ios::binary | std::ios::trunc);
//        if (!colOut.is_open()) {
//            std::cerr << "Failed to rewrite column file: " << colPath << std::endl;
//            return false;
//        }
//
//        for (size_t i = 0; i < columnValues.size(); ++i) {
//            if (i == deleteIndex) continue;
//
//            const ColVal& val = columnValues[i];
//            if (attribute->type == "integer") {
//                int64_t v = val.getIntValue();
//                colOut.write(reinterpret_cast<const char*>(&v), sizeof(v));
//            }
//            else if (attribute->type == "decimal") {
//                double d = val.getDoubleValue();
//                colOut.write(reinterpret_cast<const char*>(&d), sizeof(d));
//            }
//            else if (attribute->type == "string") {
//                const std::string& str = val.getStringValue();
//                uint16_t len = str.size();
//                colOut.write(reinterpret_cast<const char*>(&len), sizeof(len));
//                colOut.write(str.c_str(), len);
//            }
//        }
//        colOut.close();
//    }
//
//    return true;
//}
//
//bool DataDeleter::deleteRow(Relation* relation, Row* row) {
//    if (!relation || !row) return false;
//
//    // Get the primary key value from the row
//    CAttribute* pkAttr = relation->getPrimaryKey().attribute;
//    if (!pkAttr) return false;
//
//    ColVal* pkValue = nullptr;
//    for (ColVal* val : row->getColVals()) {
//        if (val->getAttribute() == pkAttr) {
//            pkValue = val;
//            break;
//        }
//    }
//
//    if (!pkValue) return false;
//    return deleteByPK(relation, *pkValue);
//}
//
//bool DataDeleter::markRowDeleted(Relation* relation, Row* row) {
//    // Implementation for soft delete - could add a deleted flag column
//    // Not implemented in this version
//    return false;
//}
//
//bool DataDeleter::purgeDeletedRows(Relation* relation) {
//    // Implementation for cleaning up soft-deleted rows
//    // Not implemented in this version
//    return false;
//}