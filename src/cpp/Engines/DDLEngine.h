#ifndef DDLEngine_H
#define DDLEngine_H

#include "../include/external_includes.h"
#include <tinyxml2.h>
//#include "ColumnStoreDB.h"
#include "../include/fsnamespace.h"
#include "../Schema/Database.h"
#include "../Schema/Schema_Element.h"
#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"
#include "../Schema/PrimaryKey.h"
#include "../Schema/Constraint.h"
#include "../Schema/PrimaryKeyConstraint.h"
#include "../Schema/ForeignKeyConstraint.h"
#include "../Schema/UniqueKeyConstraint.h"
#include "../Schema/View.h"
#include "../ComputationObjects/Query.h"
#include "DMLEngine.h"

//declaring some global variables related to the meta_metadata.json file
//fs::path meta_metadata_path;
//std::ofstream meta_metadata_file;


class DDLEngine {// Call it a DDL engine instead
//DMLEngine* dml_engine;
    //std::map<string,Database*> databases;
    //DataLoader dataLoader;
    //QueryManager queryManager;
    //ViewManager viewManager;
    //DataManipulator dataManipulator;
    //DataDeleter dataDeleter
public:
    // Loads a Database instance (i.e. its schema) from an XML instance document.
  static bool init();
    static Database loadSchemaFromXML(const std::string& xmlFilePath);
    static bool pushSchematoMeta_Metadata(const Database& db);
//    static bool createColumnStoreDBfromXMLSchema(const std::string& xmlFilePath);
    static bool changeSchema(const std::string& xmlFilePath);
    static Database* loadSchema(const std::string& xmlFilePath);
};


#endif // DDLEngine_H
