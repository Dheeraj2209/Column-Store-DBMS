#ifndef CSTOREENGINE_H
#define CSTOREENGINE_H

#include <string>
#include "ColumnStoreDB.h"

class CStoreEngine {// Call it a DDL engine instead
public:
    // Loads a Database instance (i.e. its schema) from an XML instance document.
    static Database loadFromXML(const std::string& xmlFilePath);
};

#endif // CSTOREENGINE_H
