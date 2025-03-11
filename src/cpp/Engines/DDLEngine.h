#ifndef DDLEngine_H
#define DDLEngine_H

#include "../include/external_includes.h"
//#include "ColumnStoreDB.h"
#include "../include/fsnamespace.h"
#include "../Schema/Database.h"
#include "../Schema/Schema_Element.h"
#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"
#include "../Schema/PrimaryKey.h"
#include "../Schema/Constraint.h"
#include "../Schema/View.h"

class DDLEngine {// Call it a DDL engine instead
public:
    // Loads a Database instance (i.e. its schema) from an XML instance document.
    static Database loadSchemaFromXML(const std::string& xmlFilePath);
    static bool createColumnStoreDBfromXMLSchema(const std::string& xmlFilePath);
};

#endif // DDLEngine_H
