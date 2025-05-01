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
//                    int value = table.Get<int>(row, colIndex);
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
// #include <fstream>
#include <filesystem>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "../include/Tbl.hpp"

#include <stdexcept>
#include <algorithm>

// Include the Tbl header (make sure your include paths are set correctly)
#include "../Data_Objects/ColVal.hpp"
#include "ConstraintValidator.hpp"

#include "../include/Tbl.hpp"

// Helper functions – you need to implement these in your project:
// std::unordered_set<std::string> getReferencedKeySet(Database* db, ForeignKeyConstraint* fk) {
//     std::unordered_set<std::string> refSet;
//     cout<<"getReferencedKeySet function called"<<endl;
//     std::string dbName = db->getName();
//     std::string parentRel = fk->parentTable->getName();
//     std::string parentAttr = fk->parentColumn->name;
//     cout<<"Parent Relation: "<<parentRel<<endl;
//     Relation* parentRelation = db->getRelation(parentRel);
//     // cout<<"Parent Relation pointer: "<<parentRelation<<endl;
//
//     if (!parentRelation) {
//         std::cerr << "Error: Parent relation " << parentRel << " not found.\n";
//         return refSet;
//     }
//
//     std::string childAttr = fk->childColumn->name;
//     Relation* childRelation = fk->childTable;
//
//     const auto& pattributes = parentRelation->getCAttributes();
//     cout<<"Attributes in parent relation taken "<<endl;
//     const auto& cattributes = childRelation->getCAttributes();
//
//     if (pattributes.find(parentAttr) == pattributes.end())
//     {
//         std::cerr << "Error: Attribute " << parentAttr << " not found in parent relation.\n";
//         return refSet;
//     }
//     cout<<"Attribute found in parent relation "<<endl;
//     if (cattributes.find(childAttr) == cattributes.end())
//     {
//         std::cerr << "Error: Attribute " << childAttr << " not found in child relation.\n";
//         return refSet;
//     }
//     cout<<"Attribute found in child relation "<<endl;
//     CAttribute* attr = cattributes.at(childAttr);
//     std::string filePath = "../../Databases/" + dbName + "/" + childRelation->getName() + "/" + childAttr + ".dat";
//     cout<<"File path: "<<filePath<<endl;
//
//     std::ifstream inFile(filePath, std::ios::binary);
//     cout<<"File opened "<<endl;
//     if (!inFile.is_open()) {
//         std::cerr << "Error: Unable to open file " << filePath << "\n";
//         return refSet;
//     }
//     cout<<"File:"<<filePath<<" opened successfully "<<endl;
//     if (attr->type == "integer") {
//         int val;
//         while (inFile.read(reinterpret_cast<char*>(&val), sizeof(int))) {
//             refSet.insert(std::to_string(val));
//         }
//     } else if (attr->type == "decimal") {
//         double val;
//         while (inFile.read(reinterpret_cast<char*>(&val), sizeof(double))) {
//             refSet.insert(std::to_string(val));
//         }
//     }
//     // else if (attr->type == "Date_DDMMYYYY_Type") {
//     //     Date_DDMMYYYY_Type date;
//     //     while (inFile.read(reinterpret_cast<char*>(&date), sizeof(Date_DDMMYYYY_Type))) {
//     //         refSet.insert(Date_DDMMYYYY_Type::dateToString(date));
//     //     }
//
//     // }
// else { // assume string
//         while (true) {
//             size_t len;
//             if (!inFile.read(reinterpret_cast<char*>(&len), sizeof(size_t))) break;
//             std::string val(len, '\0');
//             if (!inFile.read(&val[0], len)) break;
//             refSet.insert(val);
//         }
//     }
//     cout<<"File read successfully "<<endl;
//
//     inFile.close();
//     cout<<"File closed successfully "<<endl;
//     cout<<"Referenced Key Set: "<<endl;
//     for (auto & val: refSet) {
//         cout<<val<<endl;
//     }
//     cout<<"Referenced Key Set END"<<endl;
//     return refSet;
// }

std::unordered_set<std::string> getReferencedKeySet(
    Database* db,
    ForeignKeyConstraint* fk)
{
    cout<<"getReferencedKeySet function called"<<endl;
    std::unordered_set<std::string> refSet;
    const std::string dbName       = db->getName();
    const std::string parentRel    = fk->parentTable->getName();
    const std::string parentAttr   = fk->parentColumn->name;
    const std::string childRel     = fk->childTable->getName();
    const std::string childAttr    = fk->childColumn->name;
    cout<<"Parent Relation: "<<parentRel<<endl;
    cout<<"Child Relation: "<<childRel<<endl;
    cout<<"Parent Attribute: "<<parentAttr<<endl;
    cout<<"Child Attribute: "<<childAttr<<endl;

    // sanity checks
    Relation* parent = db->getRelation(parentRel);
    if (!parent) {
        std::cerr << "Error: Parent relation " << parentRel << " not found.\n";
        return refSet;
    }
    Relation* child = fk->childTable;
    if (!child) {
        std::cerr << "Error: Child relation " << childRel << " not found.\n";
        return refSet;
    }

    // locate the child's column file
    // std::string path = "../../Databases/" + dbName + "/" +
    //                    childRel + "/" + childAttr + ".dat";
    std::string path = "../../Databases/" + dbName + "/" +
                       childRel + "/" + childAttr + ".dat";
    cout<<"File path: "<<path<<endl;
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Unable to open " << path << "\n";
        return refSet;
    }

    // read until EOF: [isDeleted=1 byte][payload...]
    cout<<"File opened successfully "<<endl;
    cout<<"Attempting to read file..."<<endl;
    while (true) {
        uint8_t isDeleted;
        if (!in.read(reinterpret_cast<char*>(&isDeleted), sizeof(isDeleted))) break;
        cout<<"Is Deleted: "<<(int)isDeleted<<endl;
        if (fk->childColumn->type == "integer") {
            int64_t v;
            if (!in.read(reinterpret_cast<char*>(&v), sizeof(v))) break;
            cout<<"Value: "<<v<<endl;
            if (!isDeleted) refSet.insert(std::to_string(v));
        }
        else if (fk->childColumn->type == "decimal") {
            double d;
            if (!in.read(reinterpret_cast<char*>(&d), sizeof(d))) break;
            cout<<"Value: "<<d<<endl;
            if (!isDeleted) refSet.insert(std::to_string(d));
        }
        else { // string or other
            size_t len;
            if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
            std::string s(len, '\0');
            // if (!in.read(s.data(), len)) break;
            if (!in.read(&s[0], len)) break;
            cout<<"Value: "<<s<<endl;
            if (!isDeleted) refSet.insert(s);
        }
    }

    return refSet;
}

std::unordered_set<std::string> getReferencedKeySet(
    Database* db,
    PrimaryKeyConstraint* pk)
{
    cout<<"getReferencedKeySet pk function called"<<endl;
    std::unordered_set<std::string> refSet;
    const std::string dbName       = db->getName();
    const std::string relname = pk->relation->getName();
    const std::string attrname = pk->getAttribute()->name;
    // const std::string attr = pk->relation->getPrimaryKeys()[0]->name;
    Relation* rel = db->getRelation(relname);
    CAttribute* attr = pk->getAttribute();
    cout<<"Relation: "<<relname<<endl;
    cout<<"Attribute: "<<attrname<<endl;

    // sanity checks
    // Relation* parent = db->getRelation(parentRel);
    if (!rel) {
        std::cerr << "Error: Parent relation " << relname << " not found.\n";
        return refSet;
    }
    std::string path = "../../Databases/" + dbName + "/" +
                       relname + "/" + attrname + ".dat";
    cout<<"File path: "<<path<<endl;
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Unable to open " << path << "\n";
        return refSet;
    }

    // read until EOF: [isDeleted=1 byte][payload...]
    cout<<"File opened successfully "<<endl;
    cout<<"Attempting to read file..."<<endl;
    while (true) {
        uint8_t isDeleted;
        if (!in.read(reinterpret_cast<char*>(&isDeleted), sizeof(isDeleted))) break;
        cout<<"Is Deleted: "<<(int)isDeleted<<endl;
        if (pk->attribute->type == "integer") {
            int64_t v;
            if (!in.read(reinterpret_cast<char*>(&v), sizeof(v))) break;
            cout<<"Value: "<<v<<endl;
            if (!isDeleted) refSet.insert(std::to_string(v));
        }
        else if (pk->attribute->type == "decimal") {
            double d;
            if (!in.read(reinterpret_cast<char*>(&d), sizeof(d))) break;
            cout<<"Value: "<<d<<endl;
            if (!isDeleted) refSet.insert(std::to_string(d));
        }
        else { // string or other
            size_t len;
            if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
            std::string s(len, '\0');
            // if (!in.read(s.data(), len)) break;
            if (!in.read(&s[0], len)) break;
            cout<<"Value: "<<s<<endl;
            if (!isDeleted) refSet.insert(s);
        }
    }

    return refSet;
}

std::unordered_set<std::string> getReferencedKeySet(
    Database* db,
    UniqueKeyConstraint * uk)
{
    cout<<"getReferencedKeySet uk function called"<<endl;
    std::unordered_set<std::string> refSet;
    const std::string dbName       = db->getName();
    const std::string relname = uk->relation->getName();
    const std::string attrname = uk->getAttribute()->name;
    // const std::string attr = pk->relation->getPrimaryKeys()[0]->name;
    Relation* rel = db->getRelation(relname);
    CAttribute* attr = uk->getAttribute();
    cout<<"Relation: "<<relname<<endl;
    cout<<"Attribute: "<<attrname<<endl;

    // sanity checks
    // Relation* parent = db->getRelation(parentRel);
    if (!rel) {
        std::cerr << "Error: Parent relation " << relname << " not found.\n";
        return refSet;
    }
    std::string path = "../../Databases/" + dbName + "/" +
                       relname + "/" + attrname + ".dat";
    cout<<"File path: "<<path<<endl;
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Unable to open " << path << "\n";
        return refSet;
    }

    // read until EOF: [isDeleted=1 byte][payload...]
    cout<<"File opened successfully "<<endl;
    cout<<"Attempting to read file..."<<endl;
    while (true) {
        uint8_t isDeleted;
        if (!in.read(reinterpret_cast<char*>(&isDeleted), sizeof(isDeleted))) break;
        cout<<"Is Deleted: "<<(int)isDeleted<<endl;
        if (uk->attribute->type == "integer") {
            int64_t v;
            if (!in.read(reinterpret_cast<char*>(&v), sizeof(v))) break;
            cout<<"Value: "<<v<<endl;
            if (!isDeleted) refSet.insert(std::to_string(v));
        }
        else if (uk->attribute->type == "decimal") {
            double d;
            if (!in.read(reinterpret_cast<char*>(&d), sizeof(d))) break;
            cout<<"Value: "<<d<<endl;
            if (!isDeleted) refSet.insert(std::to_string(d));
        }
        else { // string or other
            size_t len;
            if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
            std::string s(len, '\0');
            // if (!in.read(s.data(), len)) break;
            if (!in.read(&s[0], len)) break;
            cout<<"Value: "<<s<<endl;
            if (!isDeleted) refSet.insert(s);
        }
    }

    return refSet;
}




bool DataLoader::loadDataFromCSV(Database* db,
                                 const std::string& relationName,
                                 const std::string& csvPath)
{
    namespace fs = std::filesystem;

    // 1) Lookup the relation
    Relation* rel = db->getRelation(relationName);
    if (!rel) {
        std::cerr << "Relation " << relationName << " not found.\n";
        return false;
    }

    // 2) Read entire CSV into memory
    cout<<"Attmepting to open CSV file: "<<csvPath<<endl;
    std::ifstream fin(csvPath, std::ios::binary);
    if (!fin) {
        std::cerr << "Failed to open CSV: " << csvPath << "\n";
        return false;
    }
    cout<<"CSV file opened successfully: "<<csvPath<<endl;
    std::stringstream buf;
    buf << fin.rdbuf();
    fin.close();
    std::string content = buf.str();
    cout<<"CSV file read successfully: "<<csvPath<<endl;
    // 3) Parse CSV with Tbl
    cout<<"Attempting to parse CSV file using Tbl: "<<csvPath<<endl;
    Tbl::Table table(content);
    if (!table) {
        std::cerr << "Failed to parse CSV: " << csvPath << "\n";
        return false;
    }
    cout<<"CSV file parsed successfully using Tbl: "<<csvPath<<endl;
    size_t numRows = table.GetNumRows();
    size_t numCols = table.GetNumColumns();
    cout<<"CSV file has "<<numRows<<" rows and "<<numCols<<" columns."<<endl;
    // 4) Build (Attribute*, columnIndex) list in schema order
    const auto& cattrs = rel->getCAttributes();            // std::map<string, CAttribute*>
    if (cattrs.size() != numCols) {
        std::cerr << "Schema/CSV column count mismatch: schema="
                  << cattrs.size() << " vs CSV=" << numCols << "\n";
        return false;
    }
    cout<<"Schema/CSV column count match: schema="
        << cattrs.size() << " vs CSV=" << numCols << "\n";

    // using CSVString = Tbl::Table<>::String;
    struct ColInfo { CAttribute* attr; size_t colIdx; };
    // std::vector<ColInfo> cols;
    std::map<std::string, ColInfo> cols;
    // cols.reserve(numCols);
    cout<<"Preparing column info..."<<endl;
    for (auto const& [colName, attr] : cattrs) {
        size_t idx = table.GetColumnIndex(colName);
        // cols.push_back({ attr, idx });
        cols[colName] = { attr, idx };

    }
    cout<<"Prepared column info."<<endl;
    // 5) Prepare per-column .dat files, bump row-count header
    cout<<"Preparing per-column .dat files..."<<endl;
    // std::vector<std::fstream> streams;
    std::map<std::string, std::fstream> streams;

    // streams.reserve(numCols);
    std::string base = "../../Databases/" + db->getName() + "/" + relationName + "/";

    std::cout << "Preparing to insert data into the following files: " << std::endl;

    for (const auto& [colName, ci] : cols) {
        fs::path p = base + ci.attr->name + ".dat";
        std::cout << p << std::endl;

        if (!fs::exists(p)) {
            std::cout << "File does not exist, creating: " << p << std::endl;
            std::ofstream init(p, std::ios::binary);
            // int zero = 0;
            // init.write(reinterpret_cast<char*>(&zero), sizeof(zero));
        }

        std::cout << "File exists, opening for read/write: " << p << std::endl;
        // std::fstream fsout(p, std::ios::in | std::ios::out | std::ios::binary);
        //
        // if (!fsout) {
        //     std::cout << "Failed to open file for read/write: " << p << std::endl;
        //     std::cerr << "Cannot open " << p << "\n";
        //     return false;
        // }
        //
        // streams[colName] = std::move(fsout);
        std::fstream fsout(p, std::ios::in | std::ios::out | std::ios::binary);
        if (!fsout) {
            std::cerr << "Cannot open " << p << "\n";
            return false;
        }

        // *** Seek to end so that all writes from here on truly append. ***
        fsout.seekp(0, std::ios::end);

        streams[colName] = std::move(fsout);

        std::cout << "File opened for read/write: " << p << std::endl;
    }



    // 6) Prepare PK/UK/FK sets
    cout<<"Preparing PK/UK/FK sets..."<<endl;
    cout<<"Loading PK/UK/FK sets... for relation: "<<relationName<<endl;
    std::unordered_map<std::string,std::unordered_set<std::string>> pkSets, ukSets, fkSets;
    // for (auto const& [name, pk] : rel->pks)    pkSets[name] = {};
    // for (auto const& [name, uk] : rel->uks)    ukSets[name] = {};

    for (auto const& [n, pk] : rel->pks) {
        // pkSets[n]={};
        // pkSets[n] = getReferencedKeySet(rel->getDatabase(), pk);
        pkSets[pk->attribute->name] = getReferencedKeySet(rel->getDatabase(), pk);
    }

    // for (auto const& [n, pk] : db->getPrimaryKeyConstraints()) {
    //     if (pk->)
    //     cout<<"Primary key: "<<pk->attribute->name<<endl;
    //     cout<<"Primary key: "<<pk->getAttribute()->name<<endl;
    //     // pkSets[n] = {};
    //     // pkSets[n] = getReferencedKeySet(rel->getDatabase(), pk);
    //     pkSets[pk->attribute->name] = getReferencedKeySet(rel->getDatabase(), pk);
    // }
    for (auto const& [n, uk] : rel->uks) {
        // ukSets[n] = {};
        // ukSets[n] = getReferencedKeySet(rel->getDatabase(), uk);
        ukSets[uk->attribute->name] = getReferencedKeySet(rel->getDatabase(), uk);
    }
    for (auto const& [name, fk] : rel->fks)
    {
        cout<<"Foreign key: parentTable: "<<fk->parentTable->name<<endl;
        cout<<"Foreign key: childTable: "<<fk->childTable->name<<endl;
        cout<<"Foreign key: parentColumn: "<<fk->parentColumn->name<<endl;
        cout<<"Foreign key: childColumn: "<<fk->childColumn->name<<endl;
        if (relationName==fk->parentTable->name){
            cout<<"Foreign key: "<<fk->parentColumn->name<<" found"<<endl;
            fkSets[fk->parentColumn->name] = getReferencedKeySet(db, fk);
        }
    }
    cout<<"Prepared PK/UK/FK sets."<<endl;
    // int newCount = 0;
    for (size_t r = 0; r < numRows; ++r)
    {
        std::cout << "Processing row " << r << std::endl;
            // vector<ColVal> rowData;
        map<string, ColVal> rowData;
        for (const auto& [attrName, ci] : cols)
        {
            std::cout << "Processing column " << attrName << std::endl;

            auto& fsout = streams.at(attrName);
            auto* attr  = ci.attr;
            size_t col  = ci.colIdx;
            cout<<"Attribute in Schema: name:"<<attr->name<<", type:"<<attr->type<<endl;
            // auto& cell = table.Get<Tbl::Table<>::String>(r, col);
            // auto& cell = table.GetData(r, col);
            // std::string raw = cell<std::string>();




            auto var = table.GetData(r, col);
            string raw;
            if (var.index() == Tbl::IntType) {
                std::cout << "Integer type data found" << std::endl;
                raw = std::to_string(std::get<int64_t>(var));
            } else if (var.index() == Tbl::DoubleType) {
                std::cout << "Double type data found" << std::endl;
                raw = std::to_string(std::get<double>(var));
            } else if (var.index() == Tbl::StringType) {
                std::cout << "String type data found" << std::endl;
                raw = std::get<Tbl::Table<>::String>(var);
            } else {
                std::cerr << "Unknown type found" << std::endl;
            }
            // std::string raw = table.Get<std::string>(r, col);
            std::cout << "Raw value: " << raw << std::endl;

            // PK check
            if (pkSets.count(attrName)) {
                if (!pkSets[attrName].insert(raw).second) {
                    std::cerr << "PK violation on " << attrName << ": " << raw << "\n";
                    return false;
                }
            }

            // UK check
            if (ukSets.count(attrName)) {
                if (!ukSets[attrName].insert(raw).second) {
                    std::cerr << "UK violation on " << attrName << ": " << raw << "\n";
                    return false;
                }
            }

            // FK check
            if (fkSets.count(attrName)) {
                cout<<"FK check for attribute: "<<attrName<<endl;
                if (fkSets[attrName].find(raw) == fkSets[attrName].end()) {
                    std::cerr << "FK violation on " << attrName << ": " << raw << "\n";

                    return false;
                }
            }


            // Write binary based on type
            cout<<"Writing data..."<<endl;
            auto data = table.GetData(r, col);
            cout<<"Data type: "<<data.index()<<endl;
            if (data.index() == Tbl::IntType) {
                std::cout << "Integer type data found" << std::endl;
                if (attr->type=="integer") {
                    std::cout << "Attribute type is integer" << std::endl;
                    int64_t v = std::get<int64_t>(data);
                    // int v2 = static_cast<int>(v);
                    ColVal cv(attr,v);
                    // rowData.push_back(cv);
                    rowData[attrName] = cv;
                    // fsout.write(reinterpret_cast<const char*>(&v), sizeof(v));
                } else if (attr->type=="decimal") {
                    std::cout << "Attribute type is decimal" << std::endl;
                    double d = static_cast<double>(std::get<int64_t>(data));
                    ColVal cv(attr, d);
                    // rowData.push_back(cv);
                    rowData[attrName] = cv;
                    // fsout.write(reinterpret_cast<const char*>(&d), sizeof(d));
                } else if (attr->type =="string")
                {
                    cout<<"Attribute type is string"<<endl;
                    std::string s = std::to_string(std::get<int64_t>(data));
                    size_t len = s.size();
                    ColVal cv(attr, s);
                    // rowData.push_back(cv);
                    rowData[attrName] = cv;
                    // size_t len = s.size();
                    // fsout.write(reinterpret_cast<const char*>(&len), sizeof(len));
                    // fsout.write(s.data(), len);
                }
                else {
                    std::cerr << "Unknown attribute type for integer data" << std::endl;
                }
            }
            else if (data.index() == Tbl::DoubleType) {
                std::cout << "Double type data found" << std::endl;
                // double d = std::get<double>(data);
                // fsout.write(reinterpret_cast<const char*>(&d), sizeof(d));
                if (attr->type == "integer") {
                    std::cout << "Attribute type is integer" << std::endl;
                    int64_t v = static_cast<int64_t>(std::get<double>(data));
                    ColVal cv(attr, v);
                    // rowData.push_back(cv);
                    rowData[attrName] = cv;
                    // fsout.write(reinterpret_cast<const char*>(&v), sizeof(v));
                } else if (attr->type == "decimal") {
                    std::cout << "Attribute type is decimal" << std::endl;
                    double d = std::get<double>(data);
                    ColVal cv(attr, d);
                    // rowData.push_back(cv);
                    rowData[attrName] = cv;
                    // fsout.write(reinterpret_cast<const char*>(&d), sizeof(d));
                } else if (attr->type == "string")
                {
                    cout<<"Attribute type is string"<<endl;
                    std::string s = std::to_string(std::get<double>(data));
                    size_t len = s.size();
                    ColVal cv(attr, s);
                    // rowData.push_back(cv);
                    rowData[attrName] = cv;
                    // fsout.write(reinterpret_cast<const char*>(&len), sizeof(len));
                    // fsout.write(s.data(), len);
                }
                else
                {
                    std::cerr<<"Unknown attribute type for double data"<<std::endl;
                }
            }
            else if (data.index() == Tbl::StringType) {
                std::cout << "String type data found" << std::endl;
                // auto s = std::get<Tbl::Table<>::String>(data);
                // size_t len = s.size();
                // fsout.write(reinterpret_cast<const char*>(&len), sizeof(len));
                // fsout.write(s.data(), len);
                if (attr->type == "integer") {
                    std::cout << "Attribute type is integer" << std::endl;
                    string s = std::get<Tbl::Table<>::String>(data);
                    int64_t v = std::stoi(s);
                    ColVal cv(attr, v);
                    // rowData.push_back(cv);
                    rowData[attrName] = cv;
                    // fsout.write(reinterpret_cast<const char*>(&v), sizeof(v));
                    // int v = std::stoll(std::get<Tbl::Table<>::String>(data));
                    // rowData.push_back(cv);
                    cout<<"\t \t \t CHECKKKKKKK  Integer data: "<<v<<endl;
                    // fsout.write(reinterpret_cast<const char*>(&v), sizeof(v));
                }
                else if (attr->type == "decimal") {
                    std::cout << "Attribute type is decimal" << std::endl;
                    string s = std::get<Tbl::Table<>::String>(data);
                    double d = std::stod(s);
                    // double d = std::stod(std::get<Tbl::Table<>::String>(data));
                    ColVal cv(attr, d);
                    // rowData.push_back(cv);
                    rowData[attrName] = cv;
                    // fsout.write(reinterpret_cast<const char*>(&d), sizeof(d));
                } else if (attr->type == "string")
                {
                    cout<<"Attribute type is string"<<endl;
                    std::string s = std::get<Tbl::Table<>::String>(data);
                    size_t len = s.size();
                    ColVal cv(attr, s);
                    // rowData.push_back(cv);
                    rowData[attrName] = cv;
                    // fsout.write(reinterpret_cast<const char*>(&len), sizeof(len));
                    // fsout.write(s.data(), len);
                }
                else {
                    std::cerr << "Unknown attribute type for string data" << std::endl;
                }
            }
            else {
                std::cerr << "Unknown type found" << std::endl;
            }
        }
        // Write the row data to the file
        cout<<"Writing row data..."<<endl;
        // int i = 0;
        for (const auto& [attrName, ci] : cols)
        {
            auto& fsout = streams.at(attrName);
            auto* attr  = ci.attr;
            size_t col  = ci.colIdx;
            // Decide isDeleted flag (always 0 for new rows)
            uint8_t isDeleted = 0;
            cout<<"Writing isDeleted flag: "<<(int)isDeleted<<endl;
            fsout.write(reinterpret_cast<const char*>(&isDeleted), sizeof(isDeleted));
            cout<<"Writing data..."<<endl;
            if (attr->type == "integer") {
                int64_t v = rowData[attrName].getIntValue();
                fsout.write(reinterpret_cast<const char*>(&v), sizeof(v));
                cout<<"Integer data"<<v<<" written"<<v<<endl;
            } else if (attr->type == "decimal") {
                double d = rowData[attrName].getDoubleValue();
                fsout.write(reinterpret_cast<const char*>(&d), sizeof(d));
                cout<<"Decimal data"<<d<<" written"<<endl;
            } else if (attr->type == "string") {
                std::string s = rowData[attrName].getStringValue();
                size_t len = s.size();
                fsout.write(reinterpret_cast<const char*>(&len), sizeof(len));
                fsout.write(s.data(), len);
                cout<<"String data"<<s<<" written"<<endl;
            }
            else {
                std::cerr << "Unknown attribute type for writing data" << std::endl;
            }
            // i++;

        }
        cout<<"Row data handled successfully."<<endl;
    }

    // 8) Close all streams

    for (auto& fsout : streams) fsout.second.close();
    cout<<"Closed all streams."<<endl;
    std::cout << "Loaded " << numRows << " rows into " << relationName << "\n";
    return true;
}


bool DataLoader::insertRow(Relation* rel, Row* row) {
    namespace fs = std::filesystem;
    const auto& attrs = rel->getCAttributes();

    // 1) Build in-memory sets for constraints
    std::unordered_map<std::string, std::unordered_set<string>> pkSets, ukSets;
    for (auto const& [n, pk] : rel->pks) {
        // pkSets[n]={};
        pkSets[n] = getReferencedKeySet(rel->getDatabase(), pk);
    }
    for (auto const& [n, uk] : rel->uks) {
        // ukSets[n] = {};
        ukSets[n] = getReferencedKeySet(rel->getDatabase(), uk);
    }
    // and FK sets for each fk:
    std::unordered_map<std::string, std::unordered_set<std::string>> fkSets;
    for (auto const& [n, fk] : rel->fks) {
        if (rel->getName()==fk->parentTable->getName())
            fkSets[n] = getReferencedKeySet(rel->getDatabase(), fk);
        // else
        // fkSets[n] = getReferencedKeySet(rel->getDatabase(), fk);
    }

    // 2) Constraint checks
    auto colvals = row->getColVals();
    for (auto& pcv : colvals) {
        auto &cv = pcv.second;
        const std::string& attrName = cv->getAttributeName();
        int64_t intval; double dval; string stringval; string raw;
        if (cv->attribute->type=="integer") {
            cout<<"Attribute type is integer"<<endl;
            intval = cv->getIntValue();
            raw = std::to_string(intval);
        }
        else if (cv->attribute->type=="decimal") {
            cout<<"Attribute type is decimal"<<endl;
            dval = cv->getDoubleValue();
            raw = std::to_string(dval);
        }
        else if (cv->attribute->type=="string") {
            cout<<"Attribute type is string"<<endl;
            stringval = cv->getStringValue();
            raw = stringval;
        }
        else {
            std::cerr << "Unknown attribute type" << std::endl;
        }
        // // PK
        // if (rel->pks.count(name)) {
        //     if (!ConstraintValidator::validatePrimaryKey(
        //             rel, *cv, rel->pks.at(name)))
        //         return false;
        // }
        // // UK
        // if (rel->uks.count(name)) {
        //     if (!ConstraintValidator::validateUniqueKey(
        //             rel, *cv, rel->uks.at(name)))
        //         return false;
        // }
        // // FK
        // if (rel->fks.count(name)) {
        //     if (!ConstraintValidator::validateForeignKey(
        //             *cv,
        //             rel->fks.at(name)))
        //         return false;
        // }
        // if (pkSets.count(attrName)) {
        //     if (!pkSets[attrName].insert(raw).second) {
        //         std::cerr << "PK violation on " << attrName << ": " << raw << "\n";
        //         return false;
        //     }
        // }
        //
        // // UK check
        // if (ukSets.count(attrName)) {
        //     if (!ukSets[attrName].insert(raw).second) {
        //         std::cerr << "UK violation on " << attrName << ": " << raw << "\n";
        //         return false;
        //     }
        // }
        //
        // // FK check
        // if (fkSets.count(attrName)) {
        //     cout<<"FK check for attribute: "<<attrName<<endl;
        //     if (fkSets[attrName].find(raw) == fkSets[attrName].end()) {
        //         std::cerr << "FK violation on " << attrName << ": " << raw << "\n";
        //
        //         return false;
        //     }
        // }

        // PK check
        if (pkSets.count(attrName)) {
            if (!pkSets[attrName].insert(raw).second) {
                std::cerr << "PK violation on " << attrName << ": " << raw << "\n";
                return false;
            }
        }

        // UK check
        if (ukSets.count(attrName)) {
            if (!ukSets[attrName].insert(raw).second) {
                std::cerr << "UK violation on " << attrName << ": " << raw << "\n";
                return false;
            }
        }

        // FK check
        if (fkSets.count(attrName)) {
            cout<<"FK check for attribute: "<<attrName<<endl;
            if (fkSets[attrName].find(raw) == fkSets[attrName].end()) {
                std::cerr << "FK violation on " << attrName << ": " << raw << "\n";

                return false;
            }
        }
    }
    Database * db = rel->getDatabase();
    // 3) Open each column file, append the new value
    std::string base = "../../Databases/" + db->getName() + "/"
                     + "/" + rel->getName() + "/";
    // ensure directory exists...
    // fs::create_directories(base);

    for (auto& pcv : colvals) {
        auto& cv = pcv.second;
        CAttribute* a = cv->getAttribute();
        std::fstream fs(base + a->name + ".dat",std::ios::in | std::ios::out | std::ios::binary);

        // bump header
        fs.seekp(0, std::ios::end);

        // isDeleted flag = 0
        uint8_t del = 0;
        fs.write(reinterpret_cast<char*>(&del), 1);

        // write payload
        if (a->type == "integer") {
            int64_t v = cv->getIntValue();
            fs.write(reinterpret_cast<char*>(&v), sizeof(v));
        }
        else if (a->type == "decimal") {
            double d = cv->getDoubleValue();
            fs.write(reinterpret_cast<char*>(&d), sizeof(d));
        }
        // else if (a->type == "date") {
        //     auto dt = cv->getDateValue();
        //     fs.write(reinterpret_cast<char*>(&dt), sizeof(dt));
        // }
        else {
            auto s = cv->getStringValue();
            size_t len = s.size();
            fs.write(reinterpret_cast<char*>(&len), sizeof(len));
            fs.write(s.data(), len);
        }
        fs.close();
    }

    return true;
}





        // if (attr->type == "integer") {
        //     cout<<"Attribute type is integer"<<endl;
        //     int v{};
        //     switch (data.index()) {
        //         // v = std::get<int64_t>(data);
        //         // case Tbl::IntType:
        //         //     cout<<"Integer type data found"<<endl;
        //             v = std::get<int64_t>(data);
        //             // break;
        //         // case Tbl::DoubleType:
        //         //     cout<<"Double type data found"<<endl;
        //         //     v = static_cast<int>(std::get<double>(data));
        //         //     break;
        //         // case Tbl::StringType:
        //         //     cout<<"String type data found"<<endl;
        //         //     v = std::stoll(std::get<Tbl::Table<>::String>(data));
        //         //     break;
        //         default:
        //             throw std::runtime_error("Unexpected variant index for integer column");
        //     }
        //     fsout.write(reinterpret_cast<const char*>(&v), sizeof(v));
        // }
        // else if (attr->type == "decimal") {
        //     cout<<"Attribute type is decimal"<<endl;
        //     double d{};
        //     // d = std::get<double>(data);
        //     switch (data.index()) {
        //         case Tbl::IntType:
        //             cout<<"Integer type data found"<<endl;
        //             d = static_cast<double>(std::get<int64_t>(data));
        //             break;
        //         // case Tbl::DoubleType:
        //         //     cout<<"Double type data found"<<endl;
        //         //     d = std::get<double>(data);
        //         //     break;
        //         // case Tbl::StringType:
        //         //     cout<<"String type data found"<<endl;
        //         //     d = std::stod(std::get<Tbl::Table<>::String>(data));
        //         //     break;
        //         default:
        //             throw std::runtime_error("Unexpected variant index for decimal column");
        //     }
        //     fsout.write(reinterpret_cast<const char*>(&d), sizeof(d));
        // }
        // else { // string
        //     cout<<"Writing string data..."<<endl;
        //     std::string s =table.Get<Tbl::Table<>::String>(r, col);
        //     // s = std::get<Tbl::Table<>::String>(data);
        //     cout<<"String data: "<<s<<endl;
        //     // if (data.index() == Tbl::StringType) {
        //     //     s = std::get<Tbl::Table<>::String>(data);
        //     // } else if (data.index() == Tbl::IntType) {
        //     //     s = std::to_string(std::get<int64_t>(data));
        //     // } else {
        //     //     s = std::to_string(std::get<double>(data));
        //     // }
        //     size_t len = s.size();
        //     fsout.write(reinterpret_cast<const char*>(&len), sizeof(len));
        //     fsout.write(s.data(), len);
        // }
        //
        // std::cout << "Column " << attrName << " processed." << std::endl;
    // }
        // newCount++;
    // }
    // // 7.1) Update row counts in column files
    // std::cout << "Updating row count headers in column files..." << std::endl;
    //
    // for (const auto& [colName, ci] : cols) {
    //     fs::path p = base + ci.attr->name + ".dat";
    //
    //     std::fstream f(p, std::ios::in | std::ios::out | std::ios::binary);
    //     if (!f) {
    //         std::cerr << "Failed to open " << p << " to update row count.\n";
    //         return false;
    //     }
    //
    //     int oldCount = 0;
    //     f.read(reinterpret_cast<char*>(&oldCount), sizeof(oldCount));
    //
    //     int newTotal = oldCount + newCount;
    //     f.seekp(0);
    //     f.write(reinterpret_cast<const char*>(&newTotal), sizeof(newTotal));
    //
    //     std::cout << "Updated row count for " << colName << ": " << oldCount << " -> " << newTotal << std::endl;
    //
    //     f.close();
    // }

    // std::cout << "Row count headers updated successfully." << std::endl;


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