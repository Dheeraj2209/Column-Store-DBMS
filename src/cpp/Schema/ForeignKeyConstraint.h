//
// Created by Pradyun Devarakonda on 31/03/25.
//

#ifndef FOREIGNKEYCONSTRAINT_H
#define FOREIGNKEYCONSTRAINT_H

#include "Constraint.h"
#include <fstream>
#include <iostream>
class Relation; // Forward declaration for Relation

class ForeignKeyConstraint : public Constraint {
public:
    Relation* parentTable;
    CAttribute* parentColumn;
    Relation* childTable;
    CAttribute* childColumn;

    ForeignKeyConstraint(const std::string& name, Relation* parentTbl, CAttribute* parentCol,
                         Relation* childTbl, CAttribute* childCol)
        : Constraint(FOREIGN_KEY), parentTable(parentTbl), parentColumn(parentCol),
          childTable(childTbl), childColumn(childCol) {
        this->name = name; // Ensure 'name' is initialized
    }
    bool create(const fs::path &basePath) const;
};

#endif //FOREIGNKEYCONSTRAINT_H
