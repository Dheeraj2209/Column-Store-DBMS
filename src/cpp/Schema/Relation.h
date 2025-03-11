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

// Relation: a table in the database.
class Relation : public Schema_Element {
public:
    std::vector<CAttribute> attributes;
    PrimaryKey primaryKey;

    // The create() method creates a directory for the relation and a .dat file for each attribute.
    virtual bool create(const fs::path &basePath) const override;
    ~Relation();
};

#endif //RELATION_H
