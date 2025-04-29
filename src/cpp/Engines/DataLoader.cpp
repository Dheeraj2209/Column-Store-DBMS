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
#include <filesystem>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "../include/Tbl.hpp"

#include <stdexcept>
#include <algorithm>

// Include the Tbl header (make sure your include paths are set correctly)
#include "../include/Tbl.hpp"

// Helper functions – you need to implement these in your project:
std::unordered_set<std::string> getReferencedKeySet(Database* db, ForeignKeyConstraint* fk) {
    std::unordered_set<std::string> refSet;
    cout<<"getReferencedKeySet function called"<<endl;
    std::string dbName = db->getName();
    std::string parentRel = fk->parentTable->getName();
    std::string parentAttr = fk->parentColumn->name;
    cout<<"Parent Relation: "<<parentRel<<endl;
    Relation* parentRelation = db->getRelation(parentRel);
    // cout<<"Parent Relation pointer: "<<parentRelation<<endl;

    if (!parentRelation) {
        std::cerr << "Error: Parent relation " << parentRel << " not found.\n";
        return refSet;
    }

    std::string childAttr = fk->childColumn->name;
    Relation* childRelation = fk->childTable;

    const auto& pattributes = parentRelation->getCAttributes();
    cout<<"Attributes in parent relation taken "<<endl;
    const auto& cattributes = childRelation->getCAttributes();

    if (pattributes.find(parentAttr) == pattributes.end())
    {
        std::cerr << "Error: Attribute " << parentAttr << " not found in parent relation.\n";
        return refSet;
    }
    cout<<"Attribute found in parent relation "<<endl;
    if (cattributes.find(childAttr) == cattributes.end())
    {
        std::cerr << "Error: Attribute " << childAttr << " not found in child relation.\n";
        return refSet;
    }
    cout<<"Attribute found in child relation "<<endl;
    CAttribute* attr = cattributes.at(childAttr);
    std::string filePath = "../../Databases/" + dbName + "/" + childRelation->getName() + "/" + childAttr + ".dat";
    cout<<"File path: "<<filePath<<endl;

    std::ifstream inFile(filePath, std::ios::binary);
    cout<<"File opened "<<endl;
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << "\n";
        return refSet;
    }
    cout<<"File:"<<filePath<<" opened successfully "<<endl;
    if (attr->type == "integer") {
        int64_t val;
        while (inFile.read(reinterpret_cast<char*>(&val), sizeof(int64_t))) {
            refSet.insert(std::to_string(val));
        }
    } else if (attr->type == "decimal") {
        double val;
        while (inFile.read(reinterpret_cast<char*>(&val), sizeof(double))) {
            refSet.insert(std::to_string(val));
        }
    }
    // else if (attr->type == "Date_DDMMYYYY_Type") {
    //     Date_DDMMYYYY_Type date;
    //     while (inFile.read(reinterpret_cast<char*>(&date), sizeof(Date_DDMMYYYY_Type))) {
    //         refSet.insert(Date_DDMMYYYY_Type::dateToString(date));
    //     }

    // }
else { // assume string
        while (true) {
            size_t len;
            if (!inFile.read(reinterpret_cast<char*>(&len), sizeof(size_t))) break;
            std::string val(len, '\0');
            if (!inFile.read(&val[0], len)) break;
            refSet.insert(val);
        }
    }
    cout<<"File read successfully "<<endl;

    inFile.close();
    cout<<"File closed successfully "<<endl;
    cout<<"Referenced Key Set: "<<endl;
    for (auto & val: refSet) {
        cout<<val<<endl;
    }
    cout<<"Referenced Key Set END"<<endl;
    return refSet;
}

// bool DataLoader::loadDataFromCSV(Database* db, const std::string& relationName, const std::string& csvPath) {
//       cout<<"Available relations in the database: "<<endl;
//       for (const auto& [name, rel] : db->getRelations()) {
//         std::cout << "Relation: " << name << "\n";
//         for (const auto& [attrName, attr] : rel->getCAttributes()) {
//           cout<<"Available attributes in the relation: "<<endl;
//             std::cout << "  Attribute: " << attrName << ", Type: " << attr->type << "\n";
//         }
//         cout<<"Available attributes in the relation END"<<endl;
//
//     }
//     cout<<"Available relations in the database END"<<endl;
//     cout<<"Checking if the relation "<<relationName<<" exists in the database: "<<endl;
//     Relation* relation = db->getRelation(relationName);
//     if (!relation) {
//         std::cerr << "Relation " << relationName << " not found.\n";
//         return false;
//     }
//
//     std::ifstream csvFile(csvPath);
//     if (!csvFile.is_open()) {
//         std::cerr << "Failed to open CSV file: " << csvPath << "\n";
//         return false;
//     }
//
//     const auto& attributes = relation->getCAttributes();
//     std::vector<std::string> attributeNames;
//     for (const auto& [name, _] : attributes) {
//         attributeNames.push_back(name);
//     }
//
//     // Constraint tracking sets
//     std::unordered_map<std::string, std::unordered_set<std::string>> pkSets;
//     std::unordered_map<std::string, std::unordered_set<std::string>> ukSets;
//     std::unordered_map<std::string, std::unordered_set<std::string>> fkSets;
//
//     for (const auto& [attrName, pk] : relation->pks) {
//         pkSets[attrName] = {};
//     }
//
//     for (const auto& [attrName, uk] : relation->uks) {
//         ukSets[attrName] = {};
//     }
//
//     for (const auto& [attrName, fk] : relation->fks) {
//         fkSets[attrName] = getReferencedKeySet(db, fk);
//     }
//
//     // Open output streams
//     std::unordered_map<std::string, std::ofstream> outStreams;
//     std::string basePath = "../../Databases/" + db->getName() + "/" + relationName + "/";
//     for (const auto& name : attributeNames) {
//         outStreams[name].open(basePath + name + ".dat", std::ios::binary | std::ios::app);
//         if (!outStreams[name]) {
//             std::cerr << "Error opening file for writing: " << basePath + name + ".dat" << "\n";
//             return false;
//         }
//     }
//
//     std::string line;
//     while (getline(csvFile, line)) {
//         std::stringstream ss(line);
//         std::string cell;
//         std::vector<std::string> row;
//         while (getline(ss, cell, ',')) {
//             row.push_back(cell);
//         }
//
//         if (row.size() != attributeNames.size()) {
//             std::cerr << "Invalid row (column count mismatch): " << line << "\n";
//             return false;
//         }
//
//         for (size_t i = 0; i < row.size(); ++i) {
//             const std::string& attrName = attributeNames[i];
//             const std::string& value = row[i];
//             const CAttribute* attr = attributes.at(attrName);
//
//             // Primary Key
//             if (pkSets.count(attrName)) {
//                 if (!pkSets[attrName].insert(value).second) {
//                     std::cerr << "Primary Key violation on " << attrName << ": " << value << "\n";
//                     return false;
//                 }
//             }
//
//             // Unique Key
//             if (ukSets.count(attrName)) {
//                 if (!ukSets[attrName].insert(value).second) {
//                     std::cerr << "Unique Key violation on " << attrName << ": " << value << "\n";
//                     return false;
//                 }
//             }
//
//             // Foreign Key
//             if (fkSets.count(attrName)) {
//                 if (fkSets[attrName].find(value) != fkSets[attrName].end()) {
//                     std::cerr << "Foreign Key violation on " << attrName << ": " << value << "\n";
//                     return false;
//                 }
//             }
//
//             // Write to disk
//             if (attr->type == "int") {
//                 int64_t val = std::stoll(value);
//                 outStreams[attrName].write(reinterpret_cast<char*>(&val), sizeof(int64_t));
//             } else if (attr->type == "float") {
//                 double val = std::stod(value);
//                 outStreams[attrName].write(reinterpret_cast<char*>(&val), sizeof(double));
//             }
// //            else if (attr->type == "Date_DDMMYYYY_Type") {
// //                Date_DDMMYYYY_Type d = Date_DDMMYYYY_Type::parse(value);
// //                outStreams[attrName].write(reinterpret_cast<char*>(&d), sizeof(Date_DDMMYYYY_Type));
// //            }
//             else {
//                 size_t len = value.length();
//                 outStreams[attrName].write(reinterpret_cast<char*>(&len), sizeof(size_t));
//                 outStreams[attrName].write(value.c_str(), len);
//             }
//         }
//     }
//
//     for (auto& [_, out] : outStreams) {
//         out.close();
//     }
//
//     csvFile.close();
//     std::cout << "Data successfully loaded into relation: " << relationName << "\n";
//     return true;
// }


// bool DataLoader::loadDataFromCSV(Database* db,
//                                  const std::string& relationName,
//                                  const std::string& csvPath)
// {
//     namespace fs = std::filesystem;
//
//     // 1) Find the relation
//     Relation* rel = db->getRelation(relationName);
//     if (!rel) {
//         std::cerr << "Relation " << relationName << " not found.\n";
//         return false;
//     }
//
//     // 2) Parse CSV using Tbl
//     std::ifstream f(csvPath);
//     if (!f.is_open()) {
//         std::cerr << "Failed to open CSV file: " << csvPath << "\n";
//         return false;
//     }
//     std::stringstream buf;
//     buf << f.rdbuf();
//     std::string content = buf.str();
//     f.close();
//
//     // 3) Now parse with Tbl:
//     Tbl::Table<> table(content);
//     if (!table) {
//         std::cerr << "Failed to parse CSV: " << csvPath << "\n";
//         return false;
//     }
//     size_t numRows = table.GetNumRows();
//     size_t numCols = table.GetNumColumns();
//
//     // 3) Gather attribute names
//     const auto& attrs = rel->getCAttributes();
//     std::vector<std::string> names;
//     names.reserve(numCols);
//     for (auto& [n, a] : attrs) names.push_back(n);
//
//     if (names.size() != numCols) {
//         std::cerr << "Schema/CSV column count mismatch.\n";
//         return false;
//     }
//
//     // 4) Build constraint–tracking sets
//     std::unordered_map<std::string,std::unordered_set<std::string>> pkSets, ukSets, fkSets;
//     for (auto& [n, pk] : rel->pks) pkSets[n] = {};
//     for (auto& [n, uk] : rel->uks) ukSets[n] = {};
//     for (auto& [n, fk] : rel->fks) fkSets[n] = getReferencedKeySet(db, fk);
//
//     // 5) Open each column file, init header if needed
//     struct Col { std::fstream fs; CAttribute* attr; };
//     std::vector<Col> cols;
//     std::string base = "../../Databases/" + db->getName() + "/" + relationName + "/";
//     fs::create_directories(base);
//
//     for (auto& colName : names) {
//         auto* attr = attrs.at(colName);
//         fs::path p = base + colName + ".dat";
//
//         // if new file, write zero header
//         if (!fs::exists(p)) {
//             std::ofstream init(p, std::ios::binary);
//             int64_t zero = 0;
//             init.write(reinterpret_cast<char*>(&zero), sizeof(zero));
//         }
//
//         // open for read/write
//         cols.emplace_back();
//         auto& c = cols.back();
//         c.attr = attr;
//         c.fs.open(p, std::ios::in|std::ios::out|std::ios::binary);
//         if (!c.fs) {
//             std::cerr << "Cannot open " << p << "\n";
//             return false;
//         }
//
//         // bump header by numRows
//         int64_t oldCount=0;
//         c.fs.read(reinterpret_cast<char*>(&oldCount), sizeof(oldCount));
//         int64_t newCount = oldCount + static_cast<int64_t>(numRows);
//         c.fs.seekp(0);
//         c.fs.write(reinterpret_cast<char*>(&newCount), sizeof(newCount));
//         c.fs.seekp(0, std::ios::end);
//     }
//
//     // 6) Iterate over every cell
//     for (size_t r = 0; r < numRows; ++r) {
//         for (size_t c = 0; c < numCols; ++c) {
//             auto& col = cols[c];
//             auto& fs  = col.fs;
//             auto* a    = col.attr;
//             const auto& variantCell = table.GetData(r, c);
//
//             // extract raw string for constraint checks
//             std::string raw;
//             switch (variantCell.index()) {
//                 case Tbl::IntType:    raw = std::to_string(std::get<int64_t>(variantCell)); break;
//                 case Tbl::DoubleType: raw = std::to_string(std::get<double>(variantCell));  break;
//                 case Tbl::StringType: raw = std::get<Tbl::Table<>::String>(variantCell);   break;
//                 default: raw = ""; break;
//             }
//
//             // PK
//             if (pkSets.count(a->name)) {
//                 if (!pkSets[a->name].insert(raw).second) {
//                     std::cerr << "PK violation on " << a->name << ": " << raw << "\n";
//                     return false;
//                 }
//             }
//             // UK
//             if (ukSets.count(a->name)) {
//                 if (!ukSets[a->name].insert(raw).second) {
//                     std::cerr << "UK violation on " << a->name << ": " << raw << "\n";
//                     return false;
//                 }
//             }
//             // FK
//             if (fkSets.count(a->name)) {
//                 if (fkSets[a->name].find(raw) == fkSets[a->name].end()) {
//                     std::cerr << "FK violation on " << a->name << ": " << raw << "\n";
//                     return false;
//                 }
//             }
//
//             // write binary payload
//             if (a->type == "integer") {
//                 int64_t v = std::get<int64_t>(variantCell);
//                 fs.write(reinterpret_cast<char*>(&v), sizeof(v));
//             }
//             else if (a->type == "decimal") {
//                 double d = std::get<double>(variantCell);
//                 fs.write(reinterpret_cast<char*>(&d), sizeof(d));
//             }
//             else if (a->type == "date") {
//                 auto s = std::get<Tbl::Table<>::String>(variantCell);
//                 Date_DDMMYYYY_Type dt = Date_DDMMYYYY_Type::parse(s);
//                 fs.write(reinterpret_cast<char*>(&dt), sizeof(dt));
//             }
//             else if (a->type == "boolean") {
//                 bool b = (raw == "true" || raw == "1");
//                 fs.write(reinterpret_cast<char*>(&b), sizeof(b));
//             }
//             else { // STRING
//                 auto& s = std::get<Tbl::Table<>::String>(variantCell);
//                 size_t len = s.size();
//                 fs.write(reinterpret_cast<char*>(&len), sizeof(len));
//                 fs.write(s.data(), len);
//             }
//         }
//     }
//
//     // 7) Close files
//     for (auto& col : cols) col.fs.close();
//
//     std::cout << "Loaded " << numRows
//               << " rows into " << relationName << "\n";
//     return true;
// }
// #include <tbl/Tbl.hpp>
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
            // int64_t zero = 0;
            // init.write(reinterpret_cast<char*>(&zero), sizeof(zero));
        }

        std::cout << "File exists, opening for read/write: " << p << std::endl;
        std::fstream fsout(p, std::ios::in | std::ios::out | std::ios::binary);

        if (!fsout) {
            std::cout << "Failed to open file for read/write: " << p << std::endl;
            std::cerr << "Cannot open " << p << "\n";
            return false;
        }

        streams[colName] = std::move(fsout);
        std::cout << "File opened for read/write: " << p << std::endl;
    }



    // 6) Prepare PK/UK/FK sets
    cout<<"Preparing PK/UK/FK sets..."<<endl;
    cout<<"Loading PK/UK/FK sets... for relation: "<<relationName<<endl;
    std::unordered_map<std::string,std::unordered_set<std::string>> pkSets, ukSets, fkSets;
    for (auto const& [name, pk] : rel->pks)    pkSets[name] = {};
    for (auto const& [name, uk] : rel->uks)    ukSets[name] = {};
    for (auto const& [name, fk] : rel->fks)
    {
        if (relationName==fk->parentTable->name){
            cout<<"Foreign key: "<<fk->parentColumn->name<<" found"<<endl;
            fkSets[fk->parentColumn->name] = getReferencedKeySet(db, fk);
        }
    }
    cout<<"Prepared PK/UK/FK sets."<<endl;
    // int newCount = 0;
    for (size_t r = 0; r < numRows; ++r) {
    std::cout << "Processing row " << r << std::endl;

    for (const auto& [attrName, ci] : cols) {
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
                fsout.write(reinterpret_cast<const char*>(&v), sizeof(v));
            } else if (attr->type=="decimal") {
                std::cout << "Attribute type is decimal" << std::endl;
                double d = static_cast<double>(std::get<int64_t>(data));
                fsout.write(reinterpret_cast<const char*>(&d), sizeof(d));
            } else if (attr->type =="string")
            {
                cout<<"Attribute type is string"<<endl;
                std::string s = std::to_string(std::get<int64_t>(data));
                size_t len = s.size();
                fsout.write(reinterpret_cast<const char*>(&len), sizeof(len));
                fsout.write(s.data(), len);
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
                fsout.write(reinterpret_cast<const char*>(&v), sizeof(v));
            } else if (attr->type == "decimal") {
                std::cout << "Attribute type is decimal" << std::endl;
                double d = std::get<double>(data);
                fsout.write(reinterpret_cast<const char*>(&d), sizeof(d));
            } else if (attr->type == "string")
            {
                cout<<"Attribute type is string"<<endl;
                std::string s = std::to_string(std::get<double>(data));
                size_t len = s.size();
                fsout.write(reinterpret_cast<const char*>(&len), sizeof(len));
                fsout.write(s.data(), len);
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
                int64_t v = std::stoll(std::get<Tbl::Table<>::String>(data));
                fsout.write(reinterpret_cast<const char*>(&v), sizeof(v));
            }
            else if (attr->type == "decimal") {
                std::cout << "Attribute type is decimal" << std::endl;
                double d = std::stod(std::get<Tbl::Table<>::String>(data));
                fsout.write(reinterpret_cast<const char*>(&d), sizeof(d));
            } else if (attr->type == "string")
            {
                cout<<"Attribute type is string"<<endl;
                std::string s = std::get<Tbl::Table<>::String>(data);
                size_t len = s.size();
                fsout.write(reinterpret_cast<const char*>(&len), sizeof(len));
                fsout.write(s.data(), len);
            }
            else {
                std::cerr << "Unknown attribute type for string data" << std::endl;
            }
        }
        else {
            std::cerr << "Unknown type found" << std::endl;
        }
        // if (attr->type == "integer") {
        //     cout<<"Attribute type is integer"<<endl;
        //     int64_t v{};
        //     switch (data.index()) {
        //         // v = std::get<int64_t>(data);
        //         // case Tbl::IntType:
        //         //     cout<<"Integer type data found"<<endl;
        //             v = std::get<int64_t>(data);
        //             // break;
        //         // case Tbl::DoubleType:
        //         //     cout<<"Double type data found"<<endl;
        //         //     v = static_cast<int64_t>(std::get<double>(data));
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
    }
        // newCount++;
    }
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
    //     int64_t oldCount = 0;
    //     f.read(reinterpret_cast<char*>(&oldCount), sizeof(oldCount));
    //
    //     int64_t newTotal = oldCount + newCount;
    //     f.seekp(0);
    //     f.write(reinterpret_cast<const char*>(&newTotal), sizeof(newTotal));
    //
    //     std::cout << "Updated row count for " << colName << ": " << oldCount << " -> " << newTotal << std::endl;
    //
    //     f.close();
    // }

    // std::cout << "Row count headers updated successfully." << std::endl;



    // 8) Close all streams

    for (auto& fsout : streams) fsout.second.close();
    cout<<"Closed all streams."<<endl;
    std::cout << "Loaded " << numRows << " rows into " << relationName << "\n";
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