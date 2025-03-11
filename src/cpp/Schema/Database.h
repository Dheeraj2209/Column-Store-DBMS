//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef DATABASE_H
#define DATABASE_H

#include "Schema_Element.h"
#include "../include/external_includes.h"

// Database Class
// The Database is a composition of Schema_Element objects.
class Database {
public:
    std::string name;
    std::vector<Schema_Element*> schemaElements; //Use a map instead of vector to store schema elements

    bool create() const;

    ~Database();//Drop the database
};


#endif //DATABASE_H
