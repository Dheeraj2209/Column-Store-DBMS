//
// Created by Pradyun Devarakonda on 12/03/25.
//

#include "DMLEngine.h"
#include "DDLEngine.h" 
bool DMLEngine::init() {
  //set the global variable meta_metadata_path
    meta_metadata_path = fs::current_path() / "meta_metadata.json";
    meta_metadata_file.open(meta_metadata_path, std::ios::app);
    if (!meta_metadata_file) {
        std::cerr << "Failed to create meta_metadata file." << std::endl;
        return false;
    }
    // Load the meta-metadata
    return loadMeta_Metadata();
}
bool DMLEngine::loadMeta_Metadata() {
    // For each database in the XML file, create a Database object and add it to the map
    // For each relation in the XML file, create a Relation object and add it to the map
    // For each view in the XML file, create a View object and add it to the map
    // For each constraint in the XML file, create a Constraint object and add it to the map
    // For each attribute in the XML file, create a CAttribute object and add it to the map
    // For each primary key in the XML file, create a PrimaryKey object and add it to the map
    // For each query in the XML file, create a Query object and add it to the map
    // For each enum in the XML file, create an Enum_Type object and add it to the map
    // For each trigger in the XML file, create a Trigger object and add it to the map
    // For each index in the XML file, create an Index object and add it to the map
    // For each user in the XML file, create a User object and add it to the map
    // For each role in the XML file, create a Role object and add it to the map
    // For each privilege in the XML file, create a Privilege object and add it to the map
    // For each authorization in the XML file, create an Authorization object and add it to the map
    // For each access in the XML file, create an Access object and add it to the map
    // For each security in the XML file, create a Security object and add it to the map
    // For each schema in the XML file, create a Schema object and add it to the map
    // For each table in the XML file, create a Table object and add it to the map
    // For each view in the XML file, create a View object and add it to the map
    // For each index in the XML file, create an Index object and add it to the map
    // For each trigger in the XML file, create a Trigger object and add it to the map
    // For each constraint in the XML file, create a Constraint object and add it to the map
    // For each attribute in the XML file, create a CAttribute object and add it to the map
    // For each primary key in the XML file, create a PrimaryKey object and add it to the map
    // For each query in the XML file, create a Query object and add it to the map
    // For each enum in the XML file, create an Enum_Type object and add it to the map
    //future feature: For each trigger in the XML file, create a Trigger object and add it to the map
    //future feature: For each index in the XML file, create an Index object and add it to the map
    //Let's start coding:
    //first retrieve all databases:
// Assuming DDLEngine.h exists and contains loadSchemaFromXML
    // Define the base directory to scan
    fs::path baseDir = "../../Databases";
    // Check if the directory exists
    if (!fs::exists(baseDir) || !fs::is_directory(baseDir)) {
        std::cerr << "Directory " << baseDir << " does not exist or is not a directory." << std::endl;
        return false;
    }

    // Static map to store loaded databases (since method is static)
    static std::map<std::string, Database*> loadedDatabases;
    bool success = true;

    // Iterate over all subdirectories in ../../Databases
    for (const auto& dirEntry : fs::directory_iterator(baseDir)) {
        if (!dirEntry.is_directory()) {
            continue; // Skip non-directory entries
        }

        std::string dbName = dirEntry.path().filename().string();
        fs::path schemaFilePath = dirEntry.path() / (dbName + "_schema.xml");

        // Check if the schema file exists
        if (!fs::exists(schemaFilePath)) {
            std::cerr << "Schema file not found for database " << dbName << ": " << schemaFilePath << std::endl;
            success = false;
            continue;
        }

        // Use DDLEngine to load the schema
//        DDLEngine ddlEngine; // Assuming DDLEngine has a default constructor
        Database* db = new Database(DDLEngine::loadSchema(schemaFilePath.string()));

        // Check if loading was successful (basic validation)
        if (db->getName().empty()) {
            std::cerr << "Failed to load schema for database " << dbName << std::endl;
            delete db;
            success = false;
            continue;
        }

        // Store the loaded database in the static map
        loadedDatabases[dbName] = db;
        std::cout << "Loaded schema for database " << dbName << " from " << schemaFilePath << std::endl;
    }

    // Optionally, update a global metadata file (e.g., meta_metadata.json)
    if (success && !loadedDatabases.empty()) {
        fs::path metaPath = meta_metadata_path; // Using global variable from DMLEngine.h
        if (metaPath.empty()) {
            metaPath = "meta_metadata.json"; // Default path if not set
        }

        std::ofstream metaFile(metaPath, std::ios::out | std::ios::trunc);
        if (!metaFile) {
            std::cerr << "Failed to open metadata file: " << metaPath << std::endl;
            success = false;
        } else {
            metaFile << "{\n  \"databases\": {\n";
            bool first = true;
            for (const auto& [name, db] : loadedDatabases) {
                if (!first) metaFile << ",\n";
                metaFile << "    \"" << name << "\": {\"schema_file\": \"../../Databases/"
                         << name << "/" << name << "_schema.xml\"}";
                first = false;
            }
            metaFile << "\n  }\n}";
            metaFile.close();
            std::cout << "Updated metadata file at " << metaPath << std::endl;
        }
    }

    // If this is meant to persist across instances, expose loadedDatabases via a static getter
    // For now, we assume this is a one-time load for initialization
    return success;
}

bool DMLEngine::loadDatafromCSV(const string& DBname, const string& CSVfile, const string& RelationName) {
    // Check if database exists
    if (this->databases.find(DBname) == this->databases.end()) {
        std::cerr << "Error: Database '" << DBname << "' not found" << std::endl;
        return false;
    }

    // Get reference to the database
    Database* db = this->databases[DBname];

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


//bool DMLEngine::insertData(const string & DBname, const string & RelationName, const std::vector<std::string>& values){
//    return dataManipulator.insertData(this->databases[DBname], RelationName, values);
//}
//bool DMLEngine::deleteData(const string & DBname, const string & RelationName, const std::vector<std::string>& values){
//    return dataDeleter.deleteData(this->databases[DBname], RelationName, values);
//}
//bool DMLEngine::updateData(const string & DBname, const string & RelationName, const std::vector<std::string>& values){
//    return dataManipulator.updateData(this->databases[DBname], RelationName, values);
//}

fs::path meta_metadata_path;
std::ofstream meta_metadata_file;
