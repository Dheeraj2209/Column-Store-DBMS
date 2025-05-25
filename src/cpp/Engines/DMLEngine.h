//
// Created by Pradyun Devarakonda on 12/03/25.
//

#ifndef DMLENGINE_H
#define DMLENGINE_H

#include "../include/external_includes.h"
#include "../include/fsnamespace.h"
#include "../Schema/Database.h"
#include "../Schema/Schema_Element.h"
#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"
#include "../Schema/PrimaryKey.h"
#include "../Schema/Constraint.h"
#include "../Schema/View.h"
#include "../ComputationObjects/Query.h"
#include "../Engines/DataLoader.h"
#include "../Engines/DataManipulator.hpp"
#include "../Engines/DataDeleter.h"
#include "../Engines/QueryManager.h"
#include "../Engines/ViewManager.h"
#include "../Engines/DataStitcher.h"
#include "../Engines/ConstraintValidator.hpp"
#include "../CustomTypes/Date_DDMMYYYY_Type.h"

//meta_metadata.json file's global variables
extern fs::path meta_metadata_path;
extern std::ofstream meta_metadata_file;


class DMLEngine {
  map<string,Database*> databases;//will be deprecated
  Database* currentDB;
  DataLoader dataLoader;
  QueryManager queryManager;
  ViewManager viewManager;
  DataManipulator dataManipulator;
  DataDeleter dataDeleter;
  DataStitcher dataStitcher;
  ConstraintValidator constraintValidator;
  public:
//    static bool loadDatafromCSV(const string & DBname const string & CSVfile, const string & RelationName);
    bool init();
    DMLEngine(){
        // Initialize the engine
        if (!init()) {
            std::cerr << "Failed to initialize DMLEngine." << std::endl;
        }
    }
    Database* getDatabase(const string& dbName) {
        if (databases.find(dbName) != databases.end()) {
            return databases[dbName];
        }
        return nullptr;
    }
    bool loadMeta_Metadata();
    bool showTables(const std::string& dbName) const;
    bool loadDatafromCSV(const string& DBname, const string& CSVfile, const string& RelationName);
    bool updateData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool selectData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool joinData(const string & DBname, const string & Relation1Name, const string & Relation2Name, const std::vector<std::string>& values);
//    static bool projectData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool aggregateData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool sortData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool groupData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//	bool row_delete(const std::string& dbName, const std::string& relName, const ColVal& pkVal); // ✅ correct
    bool row_delete(const std::string& dbName,
                           const std::string& relName,
                           string & value);
    bool row_delete(const std::string& dbName,
                           const std::string& relName,
                           int & value);
    bool row_delete(const std::string& dbName,
                           const std::string& relName,
                           double & value);
    
    bool insertRow(const std::string& relationName,
                   const std::vector<std::string>& values,
                   Database* db);
    bool printTable(const std::string& dbName,const std::string& relationName) const;

    //high level update(delete and insert)
    bool updateRow(const std::string& dbName,
                   const std::string& relName,
                   std::string& deleteKey,
                   const std::vector<std::string>& newValues);
    bool updateRow(const std::string& relationName,
                   int & value,
                   const std::vector<std::string>& values,
                   Database* db);
    bool updateRow(const std::string& relationName,
                   double & value,
                   const std::vector<std::string>& values,
                   Database* db);
    bool updateRow(const std::string& relationName,
                   const std::string & value,
                   const std::vector<std::string>& values,
                   Database* db);
    
    bool run_query(const std::string& dbName,
                   const std::string& relationName,
                   const std::string& columnNames,
                   const std::string& constraints); //working
    bool run_query(const std::string& dbName,
                   const std::string& relationName,
                   const std::string& columnNames);
    bool run_query(const std::string& dbName,
                   const std::string& relationName,
                   const std::string& columnNames,
                   const std::string& constraints,
                   const std::string& orderBy);
    bool run_query(const std::string& dbName,
                   const std::string& relationName,
                   const std::string& columnNames,
                   const std::string& constraints,
                   const std::string& orderBy,
                   const std::string& groupBy);

    bool row_undelete(const std::string& dbName,
                             const std::string& relName,
                             int& value);

};



#endif //DMLENGINE_H
