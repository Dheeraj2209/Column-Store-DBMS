//
// Created by Pradyun Devarakonda on 31/03/25.
//

#ifndef UNIQUEKEYCONSTRAINT_H
#define UNIQUEKEYCONSTRAINT_H

#include "Constraint.h"
#include <fstream>
#include <iostream>

class UniqueKeyConstraint : public Constraint {
  public:
    Relation* relation;
    std::vector<std::string> attributeRefs;
    UniqueKeyConstraint(const std::string& name, Relation* rel,
                        const std::vector<std::string>& attrs)
        : Constraint(UNIQUE), relation(rel), attributeRefs(attrs) {
        this->name = name;
    }
    bool create(const fs::path &basePath) const override;
};



#endif //UNIQUEKEYCONSTRAINT_H
