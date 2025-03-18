//
// Created by Pradyun Devarakonda on 12/03/25.
//

#include "DataLoader.h"


//bool DMLEngine::loadDatafromCSV(const & Database, const string & CSVfile, const string & RelationName){
    // Load data from CSV file into the specified relation in the specified database.
    // The CSV file should have a header row with the attribute names.
    // The order of the attributes in the CSV file should match the order of the attributes in the relation.
    // The CSV file should have one row for each tuple in the relation.
    // The CSV file should be comma-separated.
    // The CSV file should not have any quotes around the attribute values.
    // The CSV file should not have any empty lines.
    // The CSV file should not have any empty values.
    // The CSV file should not have any duplicate tuples.
    // The CSV file should not have any tuples that violate the primary key constraint.
    // The CSV file should not have any tuples that violate the foreign key constraint.
    // The CSV file should not have any tuples that violate the check constraint.
    // The CSV file should not have any tuples that violate the unique constraint.
    // The CSV file should not have any tuples that violate the not null constraint.
    // The CSV file should not have any tuples that violate the default constraint.
    // The CSV file should not have any tuples that violate the data type constraint.
    // The CSV file should not have any tuples that violate the domain constraint.
    // The CSV file should not have any tuples that violate the cardinality constraint.
    // The CSV file should not have any tuples that violate the referential integrity constraint.
    // The CSV file should not have any tuples that violate the entity integrity constraint.
    // The CSV file should not have any tuples that violate the user-defined constraint.
    // The CSV file should not have any tuples that violate the null constraint.
    // The CSV file should not have any tuples that violate the key constraint.
    // The CSV file should not have any tuples that violate the integrity constraint.
    // The CSV file should not have any tuples that violate the constraint.
    // The CSV file should not have any tuples that violate the schema constraint.
    // The CSV file should not have any tuples that violate the table constraint.
    // The CSV file should not have any tuples that violate the view constraint.
    // The CSV file should not have any tuples that violate the index constraint.
    // The CSV file should not have any tuples that violate the trigger constraint.
    // The CSV file should not have any tuples that violate the security constraint.
    // The CSV file should not have any tuples that violate the authorization constraint.
    // The CSV file should not have any tuples that violate the access constraint.
//    Relation* relation = Database.getRelation(RelationName);
//    if (!relation) {
//        cerr << "Error: Relation " << RelationName << " not found in the database.\n";
//        return false;
//    }
//
//    ifstream file(CSVfile);
//    if (!file.is_open()) {
//        cerr << "Error: Unable to open file " << CSVfile << "\n";
//        return false;
//    }
//    //scan the first line of the file to get the attribute names
//    string line;
//    getline(file, line);
//    istringstream iss(line);
//    vector<string> attributeNames;
//    string attributeName;
//    while (getline(iss, attributeName, ',')) {
//        attributeNames.push_back(attributeName);
//    }
//    //check if the number of attributes in the file matches the number of attributes in the relation
//    if (attributeNames.size() != relation->attributes.size()) {
//        cerr << "Error: Number of attributes in the file does not match the number of attributes in the relation.\n";
//        return false;
//    }
//    //check if the attribute names in the file match the attribute names in the relation
//    for (size_t i = 0; i < attributeNames.size(); ++i) {
//        if (relation->attributes.find(attributeNames[i])==relation->attributes.end()) {
//            cerr << "Error: Attribute not found" <<"\n";
//            return false;
//        }
//    }
//    //read the remaining lines of the file
//    while (getline(file, line)) {
//        istringstream iss(line);
//        vector<string> attributeValues;
//        string attributeValue;
//        while (getline(iss, attributeValue, ',')) {
//            attributeValues.push_back(attributeValue);
//        }
//        //check if the number of attribute values in the file matches the number of attributes in the relation
//        if (attributeValues.size() != relation->attributes.size()) {
//            cerr << "Error: Number of attribute values in the file does not match the number of attributes in the relation.\n";
//            return false;
//        }
//
//        for (size_t i = 0; i < attributeValues.size(); ++i) {
//            tuple.push_back(attributeValues[i]);
//        }
//        if (!relation->insertTuple(tuple)) {
//            cerr << "Error: Failed to insert tuple into relation.\n";
//            return false;
//        }
//    }
//}
// bool DataLoader::loadDataFromCSV(Database& db, const std::string& CSVfile, const std::string& relationName) {
//     // Open the CSV file
//     std::ifstream file(CSVfile);
//     if (!file.is_open()) {
//         std::cerr << "Error: Unable to open CSV file " << CSVfile << std::endl;
//         return false;
//     }
//
//     // Read the entire file content into a string
//     std::stringstream buffer;
//     buffer << file.rdbuf();
//     std::string fileContent = buffer.str();
//
//     // Parse the CSV data using Tbl
//     Tbl::Table table(fileContent);
//     if (!table) {
//         std::cerr << "Error: Failed to parse CSV data." << std::endl;
//         return false;
//     }
//
//     // Retrieve the relation and its attributes
//     Relation* relation = db.getRelation(relationName);
//     if (!relation) {
//         std::cerr << "Error: Relation " << relationName << " not found in database." << std::endl;
//         return false;
//     }
//     const auto &dbName = db.getName();
//     const auto& attributes = relation->getCAttributes();
//
//     // Ensure CSV headers match the relation's attributes
//     if (table.NumCols() != attributes.size()) {
//         std::cerr << "Error: CSV columns do not match the relation schema." << std::endl;
//         return false;
//     }
//
//     // Open column files for writing in append mode
//     std::unordered_map<std::string, std::ofstream> columnFiles;
//     for (const auto& pair : attributes) {
//         auto& attr = pair.second;
//         std::string columnFilePath = "../Databases/" + dbName + "/" + relationName + "/" + attr->name + ".dat";
//
//         columnFiles[attr->name].open(columnFilePath, std::ios::app | std::ios::binary);
//         if (!columnFiles[attr->name].is_open()) {
//             std::cerr << "Error: Unable to open column file " << columnFilePath << std::endl;
//             return false;
//         }
//     }
//
//     // Iterate over each row in the table
//     for (size_t row = 0; row < table.NumRows(); ++row) {
//         size_t colIndex = 0;
//         for (const auto& pair : attributes) {
//             const auto& attr = pair.second;
//             std::ofstream& outFile = columnFiles[attr->name];
//
//             // Write the value in binary format based on attr.type
//             if (attr->type == "int") {
//                 int value = table.GetInt(row, colIndex);
//                 outFile.write(reinterpret_cast<const char*>(&value), sizeof(int));
//             } else if (attr->type == "float") {
//                 float value = static_cast<float>(table.GetDouble(row, colIndex));
//                 outFile.write(reinterpret_cast<const char*>(&value), sizeof(float));
//             } else if (attr->type == "Date_DDMMYYYY_Type") {
//                 try {
//                     Date_DDMMYYYY_Type date = Date_DDMMYYYY_Type::parse(table.GetString(row, colIndex));
//                     outFile.write(reinterpret_cast<const char*>(&date), sizeof(Date_DDMMYYYY_Type));
//                 } catch (const std::invalid_argument& e) {
//                     std::cerr << "Error parsing date for column " << attr->name << ": " << e.what() << std::endl;
//                     return false;
//                 }
//             } else {
//                 std::string value = table.GetString(row, colIndex);
//                 size_t len = value.size();
//                 outFile.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
//                 outFile.write(value.c_str(), len);
//             }
//
//             colIndex++;
//         }
//     }
//
//     // Close all column files
//     for (auto& pair : columnFiles) {
//         pair.second.close();
//     }
//
//     return true;
// }
//
bool DataLoader::loadDataFromCSV(Database& db, const std::string& CSVfile, const std::string& relationName) {
    std::ifstream file(CSVfile);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open CSV file " << CSVfile << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContent = buffer.str();

    Tbl::Table table(fileContent);
    if (!table.isValid()) { // Ensure Table is valid
        std::cerr << "Error: Failed to parse CSV data." << std::endl;
        return false;
    }

    Relation* relation = db.getRelation(relationName);
    if (!relation) {
        std::cerr << "Error: Relation " << relationName << " not found in database." << std::endl;
        return false;
    }

    const auto &dbName = db.getName();
    const auto& attributes = relation->getCAttributes();

    if (table.NumCols() != attributes.size()) {
        std::cerr << "Error: CSV columns do not match the relation schema." << std::endl;
        return false;
    }

    std::unordered_map<std::string, std::ofstream> columnFiles;
    for (const auto& pair : attributes) {
        auto& attr = pair.second;
        std::string columnFilePath = "../Databases/" + dbName + "/" + relationName + "/" + attr->name + ".dat";

        std::ofstream& outFile = columnFiles[attr->name];
        outFile.open(columnFilePath, std::ios::app | std::ios::binary);
        if (!outFile.is_open()) {
            std::cerr << "Error: Unable to open column file " << columnFilePath << std::endl;

            // Close previously opened files
            for (auto& pair : columnFiles) {
                if (pair.second.is_open()) pair.second.close();
            }
            return false;
        }
    }

    // Iterate over each row
    for (size_t row = 0; row < table.NumRows(); ++row) {
        size_t colIndex = 0;  // Reset column index for each row

        for (const auto& pair : attributes) {
            const auto& attr = pair.second;
            std::ofstream& outFile = columnFiles[attr->name];

            try {
                if (attr->type == "int") {
                    int value = table.GetInt(row, colIndex);
                    outFile.write(reinterpret_cast<const char*>(&value), sizeof(int));
                } else if (attr->type == "float") {
                    float value = static_cast<float>(table.GetDouble(row, colIndex));
                    outFile.write(reinterpret_cast<const char*>(&value), sizeof(float));
                } else if (attr->type == "Date_DDMMYYYY_Type") {
                    // Date_DDMMYYYY_Type date = Date_DDMMYYYY_Type::parse(table.GetString(row, colIndex));
                    // std::string binaryDate = date.toBinary(); // Ensure a proper serialization method
                    // outFile.write(binaryDate.data(), binaryDate.size());
                    Date_DDMMYYYY_Type date = Date_DDMMYYYY_Type::parse(table.GetString(row, colIndex));
                    outFile.write(reinterpret_cast<const char*>(&date), sizeof(Date_DDMMYYYY_Type));
                } else {
                    std::string value = table.GetString(row, colIndex);
                    size_t len = value.size();
                    outFile.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
                    outFile.write(value.c_str(), len);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error processing column " << attr->name << " in row " << row << ": " << e.what() << std::endl;

                // Cleanup before returning
                for (auto& pair : columnFiles) {
                    pair.second.close();
                }
                return false;
            }

            colIndex++;
        }
    }

    // Close all files
    for (auto& pair : columnFiles) {
        pair.second.close();
    }

    return true;
}
