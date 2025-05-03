//
// Created by Pradyun Devarakonda on 12/03/25.
//

#include "DMLEngine.h"
#include "DDLEngine.h"
#include "../Schema/Database.h"

bool DMLEngine::init() {
  //set the global variable meta_metadata_path
    meta_metadata_path = fs::current_path() / "meta_metadata.json";
    meta_metadata_file.open(meta_metadata_path, std::ios::app);
    if (!meta_metadata_file) {
        std::cerr << "Failed to create meta_metadata file." << std::endl;
        return false;
    }
    // Load the meta-metadata
    return this->loadMeta_Metadata();
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
        Database* db = DDLEngine::loadSchema(schemaFilePath.string());

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

    databases = loadedDatabases; // Store loaded databases in the DMLEngine instance

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
    bool success = dataLoader.loadDataFromCSV(db, RelationName, CSVfile);

    if (success) {
        std::cout << "Successfully loaded data from " << CSVfile
                  << " into " << DBname << "." << RelationName << std::endl;
    } else {
        std::cerr << "Failed to load data from " << CSVfile
                  << " into " << DBname << "." << RelationName << std::endl;
    }

    return success;
}

bool DMLEngine::insertRow(const std::string& relationName,
                         const std::vector<std::string>& values,
                         Database* db)
{
    // 1) find relation
    Relation* rel = db->getRelation(relationName);
    if (!rel) {
        std::cerr << "Relation " << relationName << " not found\n";
        return false;
    }

    const auto& attrs = rel->getCAttributes();
    if (values.size() != attrs.size()) {
        std::cerr << "Wrong number of values for INSERT\n";
        return false;
    }

    // 2) build a Row
    Row* row = new Row(rel);
    size_t i = 0;
    for (auto const& [colName, attr] : attrs) {
        const std::string& raw = values[i++];
        ColVal* cv = nullptr;

        if (raw.empty() && attr->isNullable) {
            cv = new ColVal(attr, /*isNull=*/true);
        }
        else if (attr->type == "integer") {
            int64_t v = std::stoll(raw);
            cv = new ColVal(attr, v);
        }
        else if (attr->type == "decimal") {
            double d = std::stod(raw);
            cv = new ColVal(attr, d);
        }
        else if (attr->type == "date") {
            auto dt = Date_DDMMYYYY_Type::parse(raw);
            cv = new ColVal(attr, dt);
        }
        else { // string
            cv = new ColVal(attr, raw);
        }

        row->addColVal(cv);
    }

    // 3) hand off to DataLoader
    bool ok = dataLoader.insertRow(rel, row);
    if (!ok) {
        delete row;
    }
    return ok;
}

bool DMLEngine::updateRow(const std::string& dbName,
                          const std::string& relName,
                          std::string& deleteKey,
                          const std::vector<std::string>& newValues)

{
    // 1) fetch the database object
    Database* db = getDatabase(dbName);
    if (!db) {
        std::cerr << "Database " << dbName << " not found.\n";
        return false;
    }
    CAttribute* pkAttr = db->getRelation(relName)->getPrimaryKey().attribute;
    if (!pkAttr) {
        std::cerr << "Primary key not found for relation " << relName << "\n";
        return false;
    }
    if (pkAttr->type=="integer") {
        int v = std::stoll(deleteKey);
        if (!row_delete(dbName, relName, v)) {
            std::cerr << "Failed to delete old row in " << relName
                      << " with key " << deleteKey << "\n";
            return false;
        }
        if (!insertRow(relName, newValues, db)) {
            std::cerr << "Failed to insert updated row into " << relName << "\n";
            return false;
        }
    }
    else if (pkAttr->type=="decimal") {
        double d = std::stod(deleteKey);
        if (!row_delete(dbName, relName, d)) {
            std::cerr << "Failed to delete old row in " << relName
                      << " with key " << deleteKey << "\n";
            return false;
        }
        if (!insertRow(relName, newValues, db)) {
            std::cerr << "Failed to insert updated row into " << relName << "\n";
            return false;
        }
    }
    else if (pkAttr->type=="string") {

        if (!row_delete(dbName, relName, deleteKey)) {
            std::cerr << "Failed to delete old row in " << relName
                      << " with key " << deleteKey << "\n";
            return false;
        }
        if (!insertRow(relName, newValues, db)) {
            std::cerr << "Failed to insert updated row into " << relName << "\n";
            return false;
        }
    }
    else{
        std::cerr << "Unsupported primary key type: " << pkAttr->type << "\n";
        return false;
    }
    // 2) delete the old tuple


    // 3) insert the new tuple
    // if (!insertRow(relName, newValues, db)) {
    //     std::cerr << "Failed to insert updated row into " << relName << "\n";
    //     return false;
    // }

    return true;
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


// UPDAE DATA high level call
//bool DMLEngine::updateData(const std::string& DBname, const std::string& RelationName, const std::vector<std::string>& values) {
//    if (databases.find(DBname) == databases.end()) {
//        std::cerr << "Error: Database '" << DBname << "' not found" << std::endl;
//        return false;
//    }
//
//    Database* db = databases[DBname];
//    Relation* relation = db->getRelation(RelationName);
//    if (!relation) {
//        std::cerr << "Error: Relation '" << RelationName << "' not found in database '" << DBname << "'" << std::endl;
//        return false;
//    }
//
//    // Create a Row object with the updated values
//    Row row(values, relation);
//
//    // Delegate to DataManipulator
//    return dataManipulator.updateTuple(relation, &row);
//}

bool DMLEngine::updateData(const std::string& DBname, const std::string& RelationName, const std::vector<std::string>& values) {
    if (databases.find(DBname) == databases.end()) {
        std::cerr << "Error: Database '" << DBname << "' not found" << std::endl;
        return false;
    }

    Database* db = databases[DBname];
    auto relation = db->getRelation(RelationName);
    if (!relation) {
        std::cerr << "Error: Relation '" << RelationName << "' not found in database '" << DBname << "'" << std::endl;
        return false;
    }

    Row row(values, relation);
    return dataManipulator.updateTuple(relation, &row);
}

//DELETE ROW {SOFT DELETE}

bool DMLEngine::row_delete(const std::string& dbName,
                           const std::string& relName,
                           string & value)
{
    // 1) get the Database & Relation
    Database* db = databases[dbName];
    if (!db) {
        std::cerr<<"DB "<<dbName<<" not found\n";
        return false;
    }
    Relation* rel = db->getRelation(relName);
    if (!rel) {
        std::cerr<<"Relation "<<relName<<" not found\n";
        return false;
    }
    ColVal pkColVal(rel->getPrimaryKey().attribute,value);
    // 2) call DataDeleter
    if (!DataDeleter::deleteRow(rel, pkColVal)) {
        std::cerr<<"Failed to delete row with PK: "<<pkColVal.getStringValue()<<"\n";
//        pkVal.getStringValue() <<"\n";
        return false;
    }

    std::cout<<"Row deleted successfully (soft) for PK="<<pkColVal.getStringValue()<<"\n";
//              <<pkVal.getStringValue()<<"\n";
    return true;
}

bool DMLEngine::row_delete(const std::string& dbName,
                           const std::string& relName,
                           int & value)
{
    // 1) get the Database & Relation
    Database* db = databases[dbName];
    if (!db) {
        std::cerr<<"DB "<<dbName<<" not found\n";
        return false;
    }
    Relation* rel = db->getRelation(relName);
    if (!rel) {
        std::cerr<<"Relation "<<relName<<" not found\n";
        return false;
    }
    auto val2 = static_cast<int64_t>(value);
    ColVal pkColVal(rel->getPrimaryKey().attribute,val2);
    // 2) call DataDeleter
    if (!DataDeleter::deleteRow(rel, pkColVal)) {
        std::cerr<<"Failed to delete row with PK: "<<pkColVal.getIntValue()<<"\n";
//        pkVal.getStringValue() <<"\n";
        return false;
    }

    std::cout<<"Row deleted successfully (soft) for PK="<<pkColVal.getIntValue()<<"\n";
//              <<pkVal.getStringValue()<<"\n";
    return true;
}



bool DMLEngine::row_delete(const std::string& dbName,
                           const std::string& relName,
                           double & value)
{
    // 1) get the Database & Relation
    Database* db = databases[dbName];
    if (!db) {
        std::cerr<<"DB "<<dbName<<" not found\n";
        return false;
    }
    Relation* rel = db->getRelation(relName);
    if (!rel) {
        std::cerr<<"Relation "<<relName<<" not found\n";
        return false;
    }
    ColVal pkColVal(rel->getPrimaryKey().attribute,value);
    // 2) call DataDeleter
    if (!DataDeleter::deleteRow(rel, pkColVal)) {
        std::cerr<<"Failed to delete row with PK: "<<pkColVal.getDoubleValue()<<"\n";
//        pkVal.getStringValue() <<"\n";
        return false;
    }

    std::cout<<"Row deleted successfully (soft) for PK="<<pkColVal.getDoubleValue()<<"\n";
//              <<pkVal.getStringValue()<<"\n";
    return true;
}


bool DMLEngine::row_undelete(const std::string& dbName,
                             const std::string& relName,
                             int& value)
{
    // 1) get the Database & Relation
    Database* db = databases[dbName];
    if (!db) {
        std::cerr << "DB " << dbName << " not found\n";
        return false;
    }

    Relation* rel = db->getRelation(relName);
    if (!rel) {
        std::cerr << "Relation " << relName << " not found\n";
        return false;
    }

    // 2) construct the primary key value
    auto val2 = static_cast<int64_t>(value);
    ColVal pkColVal(rel->getPrimaryKey().attribute, val2);

    // 3) call undelete in DataDeleter
    if (!DataDeleter::undeleteRow(rel, pkColVal)) {
        std::cerr << "Failed to undelete row with PK: " << pkColVal.getIntValue() << "\n";
        return false;
    }

    std::cout << "Row undeleted successfully for PK=" << pkColVal.getIntValue() << "\n";
    return true;
}

bool DMLEngine::run_query(const std::string& dbName,
                          const std::string& relationName,
                          const std::string& columnNames,
                          const std::string& constraints)
{

    std::cout << "Running query on " << dbName << "." << relationName
              << " with columns: " << columnNames
              << " and constraints: " << constraints << std::endl;

    // 1) get the Database & Relation
    Database* db = databases[dbName];
    if (!db) {
        std::cerr << "DB " << dbName << " not found\n";
        return false;
    }
    Relation* rel = db->getRelation(relationName);
    if (!rel) {
        std::cerr << "Relation " << relationName << " not found\n";
        return false;
    }

    // 2) parse the column names and constraints
    std::vector<std::string> colNames;
    std::istringstream colStream(columnNames);
    std::string colName;
    while (std::getline(colStream, colName, ',')) {
        colNames.push_back(colName);
    }

    std::vector<std::string> constraintsVec;
    std::istringstream constraintStream(constraints);
    std::string constraint;
    while (std::getline(constraintStream, constraint, ',')) {
        constraintsVec.push_back(constraint);
    }
    
    // 3) create a Query object
    Query query;
    query.setParticipating_relations({ relationName });
    query.setResultcols(colNames);
    query.setConditions(constraintsVec);
    query.setOrderbycols({}); // Assuming no ORDER BY for now
    
    Table* resultTable = NULL;
    if (!queryManager.executeQuery(db, query, resultTable)) {
        std::cerr << "Query execution failed\n";
        return false;
    }

    return true;

}

bool DMLEngine::printTable(const std::string& dbName, const std::string& relationName) const {
    namespace fs = std::filesystem;
    // Database* db = getDatabase(dbName);
    Database* db = databases.at(dbName);
    // 1) Find the relation
    Relation* rel = db->getRelation(relationName);
    if (!rel) {
        std::cerr << "Relation " << relationName << " not found.\n";
        return false;
    }

    // 2) Gather attributes in schema order
    const auto& attrMap = rel->getCAttributes(); // map<string,CAttribute*>
    std::vector<CAttribute*> attrs;
    attrs.reserve(attrMap.size());
    for (auto const& [name, attr] : attrMap) {
        attrs.push_back(attr);
    }

    // 3) Open each column file for binary reading
    std::string base = "../../Databases/" + db->getName() + "/" + relationName + "/";
    struct ColIn { CAttribute* attr; std::ifstream in; };
    std::vector<ColIn> cols;
    cols.reserve(attrs.size());

    for (auto* attr : attrs) {
        fs::path p = base + attr->name + ".dat";
        std::ifstream in(p, std::ios::binary);
        if (!in) {
            std::cerr << "Cannot open column file: " << p << "\n";
            return false;
        }
        cols.push_back({ attr, std::move(in) });
    }

    // 4) Print a header row
    for (auto* attr : attrs) {
        std::cout << std::setw(20) << std::left << attr->name;
    }
    std::cout << "\n";
    for (size_t i = 0; i < attrs.size(); ++i) {
        std::cout << std::string(20, '-');
    }
    std::cout << "\n";

    // 5) Read in lockstep until the first column hits EOF
    while (true) {
        // Attempt to read the deleted-flag from the first column
        uint8_t flag0;
        if (!cols[0].in.read(reinterpret_cast<char*>(&flag0), sizeof(flag0))) {
            // EOF reached
            break;
        }

        // For each column, read its own flag and value
        std::vector<std::string> row;
        row.reserve(cols.size());
        for (size_t i = 0; i < cols.size(); ++i) {
            auto& [attr, in] = cols[i];
            uint8_t flag = (i == 0 ? flag0 : 0);
            if (i != 0) {
                // for columns beyond the first, read & discard their flag
                in.read(reinterpret_cast<char*>(&flag), sizeof(flag));
            }

            // now read the actual data
            std::string cell;
            if (attr->type == "integer") {
                int64_t v;
                in.read(reinterpret_cast<char*>(&v), sizeof(v));
                cell = std::to_string(v);
            }
            else if (attr->type == "decimal") {
                double d;
                in.read(reinterpret_cast<char*>(&d), sizeof(d));
                cell = std::to_string(d);
            }
            else if (attr->type == "date") {
                Date_DDMMYYYY_Type dt;
                in.read(reinterpret_cast<char*>(&dt), sizeof(dt));
                cell = dt.toString();  // implement this in your Date class
            }
            else { // string
                size_t len;
                in.read(reinterpret_cast<char*>(&len), sizeof(len));
                std::string s(len, '\0');
                in.read(&s[0], len);
                cell = s;
            }

            row.push_back(cell);
        }

        // 6) Skip if deleted
        if (flag0 == 1) {
            continue;
        }

        // 7) Print the row
        for (auto& cell : row) {
            std::cout << std::setw(20) << std::left << cell;
        }
        std::cout << "\n";
    }

    // 8) Close files
    for (auto& c : cols) {
        c.in.close();
    }

    return true;
}
fs::path meta_metadata_path;
std::ofstream meta_metadata_file;
