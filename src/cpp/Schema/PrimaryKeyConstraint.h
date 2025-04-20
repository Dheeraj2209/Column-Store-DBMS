//
// Created by Pradyun Devarakonda on 31/03/25.
//

#ifndef PRIMARYKEYCONSTRAINT_H
#define PRIMARYKEYCONSTRAINT_H

#include "Constraint.h"
#include <fstream>
#include <iostream>



class PrimaryKeyConstraint : public Constraint {
public:
    Relation* relation;
    std::vector<std::string> attributeRefs;

    PrimaryKeyConstraint(const std::string& name, Relation* rel,
                         const std::vector<std::string>& attrs)
        : Constraint(PRIMARY_KEY), relation(rel), attributeRefs(attrs) {
        this->name = name;
    }
    bool create(const fs::path &basePath) const override;
    std::string getName();
};

#endif //PRIMARYKEYCONSTRAINT_H
