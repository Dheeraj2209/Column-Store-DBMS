//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "Schema_Element.h"
#include "../include/fsnamespace.h"
#include "Relation.h"
#include "CAttribute.h"
// Constraint: represents a constraint. Here we use a single class to represent both foreign key and unique constraints.
// The 'type' member distinguishes them.
class Constraint : public Schema_Element {
public:
    enum Type {
        PRIMARY_KEY,
        FOREIGN_KEY,
        UNIQUE
    };
    Type type;
    // For a unique constraint:
    Constraint(Type type) : type(type) {}
    virtual bool create(const fs::path &basePath) const override = 0;
    virtual ~Constraint() {}
};


#endif //CONSTRAINT_H
