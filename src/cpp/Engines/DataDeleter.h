//
// Created by Pradyun Devarakonda on 12/03/25.
//
#ifndef DATADELETER_H
#define DATADELETER_H

#include "../include/external_includes.h"
#include "../Schema/Relation.h"
#include <string>

// DataDeleter is responsible for deleting a tuple from a relation.
// Deletion in a column-store may be implemented as a logical delete (marking as deleted),
// or by rewriting column files. In this version 0.0, we simulate deletion.
class DataDeleter {
public:
    // Deletes the tuple (row) at rowIndex from the given relation.
    // Returns true on successful deletion.
    bool deleteTuple(Relation* relation, int rowIndex);
};

#endif // DATADELETER_H
