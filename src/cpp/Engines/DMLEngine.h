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
#include "../Engines/DataManipulator.h"
#include "../Engines/DataDeleter.h"
#include "../Engines/QueryManager.h"
#include "../Engines/ViewManager.h"
#include "../Engines/DataStitcher.h"
#include "../CustomTypes/Date_DDMMYYYY_Type.h"

//meta_metadata.json file's global variables
extern fs::path meta_metadata_path;
extern std::ofstream meta_metadata_file;


class DMLEngine {
  map<string,Database*> databases;
  DataLoader dataLoader;
  QueryManager queryManager;
  ViewManager viewManager;
  DataManipulator dataManipulator;
  DataDeleter dataDeleter;
  public:
//    static bool loadDatafromCSV(const string & DBname const string & CSVfile, const string & RelationName);
    static bool init();
    static bool loadMeta_Metadata();
    bool loadDatafromCSV(const string& DBname, const string& CSVfile, const string& RelationName);
//    static bool insertData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool deleteData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool updateData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool selectData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool joinData(const string & DBname, const string & Relation1Name, const string & Relation2Name, const std::vector<std::string>& values);
//    static bool projectData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool aggregateData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool sortData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);
//    static bool groupData(const string & DBname, const string & RelationName, const std::vector<std::string>& values);

};



#endif //DMLENGINE_H
