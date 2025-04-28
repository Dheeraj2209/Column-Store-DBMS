//
// Created by Pradyun Devarakonda on 31/03/25.
//

#ifndef UNIQUEKEYCONSTRAINT_H
#define UNIQUEKEYCONSTRAINT_H

#include "Constraint.h"
#include <fstream>
#include <iostream>
#include "CAttribute.h"
class Relation; // Forward declaration for Relation
class UniqueKeyConstraint : public Constraint {
  public:
    Relation* relation;
    CAttribute* attribute;
    std::vector<std::string> attributeRefs;
    UniqueKeyConstraint(const std::string& name, Relation* rel,
                        const std::vector<std::string>& attrs)
        : Constraint(UNIQUE), relation(rel), attributeRefs(attrs) {
        this->name = name;
    }
    bool create(const fs::path &basePath) const;
    std::string getName() {
        return this->name;
    }
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



#endif //UNIQUEKEYCONSTRAINT_H
