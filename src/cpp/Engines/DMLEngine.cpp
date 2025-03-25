//
// Created by Pradyun Devarakonda on 12/03/25.
//

#include "DMLEngine.h"

bool DMLEngine::loadDatafromCSV(const string& DBname, const string& CSVfile, const string& RelationName) {
    // Check if database exists
    if (this->databases.find(DBname) == this->databases.end()) {
        std::cerr << "Error: Database '" << DBname << "' not found" << std::endl;
        return false;
    }

    // Get reference to the database
    Database& db = this->databases[DBname];

    // Delegate to DataLoader's static method
    bool success = DataLoader::loadDataFromCSV(db, CSVfile, RelationName);

    if (success) {
        std::cout << "Successfully loaded data from " << CSVfile
                  << " into " << DBname << "." << RelationName << std::endl;
    } else {
        std::cerr << "Failed to load data from " << CSVfile
                  << " into " << DBname << "." << RelationName << std::endl;
    }

    return success;
}

bool DMLEngine::insertData(const string & DBname, const string & RelationName, const std::vector<std::string>& values){
    return dataManipulator.insertData(this->databases[DBname], RelationName, values);
}
bool DMLEngine::deleteData(const string & DBname, const string & RelationName, const std::vector<std::string>& values){
    return dataDeleter.deleteData(this->databases[DBname], RelationName, values);
}
bool DMLEngine::updateData(const string & DBname, const string & RelationName, const std::vector<std::string>& values){
    return dataManipulator.updateData(this->databases[DBname], RelationName, values);
}
