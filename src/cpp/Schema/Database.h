//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef DATABASE_H
#define DATABASE_H

#include "Schema_Element.h"
#include "../include/external_includes.h"

// Database Class
// The Database is a composition of Schema_Element objects.
class Database{
    std::string name;
    std::map<string,Schema_Element*> schemaElements; //Use a map instead of vector to store schema elements
    std::string xmlFilePath;
public:
    Database();
    Database(const std::string& xmlFilePath);
    string getName() const;
    std::map<string,Schema_Element*> getSchemaElements() const;
    std::string getXmlFilePath() const;
    void setName(const std::string& name);
    void setSchemaElements(const std::map<string,Schema_Element*>& schemaElements);
    void setXmlFilePath(const std::string& xmlFilePath);
    bool create() const;

    ~Database();//Drop the database
};


#endif //DATABASE_H
