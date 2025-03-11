#ifndef DDLEngine_H
#define DDLEngine_H

#include <string>
#include "ColumnStoreDB.h"

class DDLEngine {// Call it a DDL engine instead
public:
    // Loads a Database instance (i.e. its schema) from an XML instance document.
    static Database loadSchemaFromXML(const std::string& xmlFilePath);
};

#endif // DDLEngine_H
