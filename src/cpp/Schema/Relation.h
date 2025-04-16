//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef RELATION_H
#define RELATION_H
#include "../include/fsnamespace.h"
#include "../include/external_includes.h"
#include "Schema_Element.h"
#include "CAttribute.h"
#include "PrimaryKey.h"
using namespace std;
// Relation: a table in the database.
class Relation : public Schema_Element {
  std::map<string,CAttribute*> cattributes;
  PrimaryKey primaryKey;
public:
  std::map<string,CAttribute*> getCAttributes() const;
PrimaryKey getPrimaryKey() const;
bool setCAttributes(const std::map<std::string, CAttribute*>& attributes);
bool setPrimaryKey(const PrimaryKey& primaryKey);
bool addCAttribute(const CAttribute* attribute);
bool removeCAttribute(const std::string& attributeName);
CAttribute* getCAttribute(const std::string& attributeName);

    // The create() method creates a directory for the relation and a .dat file for each attribute.
    virtual bool create(const fs::path &basePath) const override;
    ~Relation();
};

#endif //RELATION_H
