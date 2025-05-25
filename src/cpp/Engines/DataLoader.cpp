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
    string relationName = rel->getName();
    Database* db  = rel->getDatabase();
    // 1) Build in-memory sets for constraints
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



