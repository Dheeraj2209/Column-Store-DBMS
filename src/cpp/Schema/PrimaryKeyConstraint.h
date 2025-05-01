//
// Created by Pradyun Devarakonda on 31/03/25.
//

#ifndef PRIMARYKEYCONSTRAINT_H
#define PRIMARYKEYCONSTRAINT_H

// #include "../include/external_includes.h"
#include <string>
#include "Constraint.h"
#include "PrimaryKey.h"
#include <fstream>
#include <iostream>
#include "CAttribute.h"
class Relation; // Forward declaration for Relation
class PrimaryKeyConstraint : public Constraint {
public:
    Relation* relation;
    CAttribute* attribute;
    std::vector<std::string> attributeRefs;
    PrimaryKey* primaryKey;
    PrimaryKeyConstraint() : Constraint(PRIMARY_KEY) {}
    PrimaryKeyConstraint(const std::string& name, Relation* rel,
                         const std::vector<std::string>& attrs)
        : Constraint(PRIMARY_KEY), relation(rel), attributeRefs(attrs) {

        this->name = name;
    }
    // PrimaryKeyConstraint(const std::string& name, Relation* rel, const std::vector<std::string>& attrs, std::string attrname);
    PrimaryKeyConstraint(const std::string& name, Relation* rel, const std::vector<std::string>& attrs, CAttribute* attr);
    //     : Constraint(PRIMARY_KEY), relation(rel), attributeRefs(attrs){
    //     this->attribute = rel->getCAttribute(attrname);
    //     this->name = name;
    // }
    bool create(const fs::path &basePath) const;
    std::string getName();
    std::vector<std::string> getAttributeRefs() const {
        return attributeRefs;
    }
    Relation* getRelation() const {
        return relation;
    }
    CAttribute* getAttribute() const {
        return attribute;
    }

};

#endif //PRIMARYKEYCONSTRAINT_H
