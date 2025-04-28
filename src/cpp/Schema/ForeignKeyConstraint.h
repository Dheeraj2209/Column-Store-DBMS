//
// Created by Pradyun Devarakonda on 31/03/25.
//

#ifndef FOREIGNKEYCONSTRAINT_H
#define FOREIGNKEYCONSTRAINT_H

#include "Constraint.h"
#include "Relation.h"
#include "CAttribute.h"
#include <fstream>
#include <iostream>
//class Relation; // Forward declaration for Relation

class ForeignKeyConstraint : public Constraint {
public:
    Relation* parentTable;
      std::string DatabaseName;

    CAttribute* parentColumn;

   std::string childRelationName;
    Relation* childTable;
    CAttribute* childColumn;

    ForeignKeyConstraint(const std::string& name, Relation* parentTbl, CAttribute* parentCol,
                         Relation* childTbl, CAttribute* childCol)
        : Constraint(FOREIGN_KEY), parentTable(parentTbl), parentColumn(parentCol),
          childTable(childTbl), childColumn(childCol) {
        this->name = name; // Ensure 'name' is initialized
    }
    bool create(const fs::path &basePath) const;
    std::string getName() const {
        return name;
    }
    Relation* getParentTable() const {
        return parentTable;
    }
    CAttribute* getParentColumn() const {
        return parentColumn;
    }
    Relation* getChildTable() const {
        return childTable;
    }
    CAttribute* getChildColumn() const {
        return childColumn;
    }
    std::string getDatabaseName() const {
        return DatabaseName;
    }
};

#endif // FOREIGNKEYCONSTRAINT_H
