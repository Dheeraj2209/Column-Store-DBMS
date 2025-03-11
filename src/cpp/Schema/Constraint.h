//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "Schema_Element.h"
#include "../include/fsnamespace.h"
// Constraint: represents a constraint. Here we use a single class to represent both foreign key and unique constraints.
// The 'type' member distinguishes them.
class Constraint : public Schema_Element {
public:
    std::string type;  // e.g., "ForeignKey" or "Unique"

    // For a foreign key constraint:
    std::string parentTable;
    std::string parentColumn;
    std::string childTable;
    std::string childColumn;

    // For a unique constraint:
    std::string relation; // relation name on which this unique constraint applies.
    std::vector<std::string> attributeRefs;

    // The create() method writes a summary entry into a constraints file.
    virtual bool create(const fs::path &basePath) const override;
    ~Constraint();
};


#endif //CONSTRAINT_H
