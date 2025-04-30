//
// Created by Pradyun Devarakonda on 12/03/25.
//
#ifndef DATADELETER_H
#define DATADELETER_H

#include "../include/external_includes.h"
#include "../Schema/Relation.h"
#include "../include/fsnamespace.h"
#include <string>
#include "../Schema/CAttribute.h"
#include "../Data_Objects/Row.hpp"
#include "../Data_Objects/ColVal.hpp"
//#include "../Data_Objects/ColContainer.hpp"
//#include "../Data_Objects/ColPage.h"


// DataDeleter is responsible for deleting a tuple from a relation.
// Deletion in a column-store may be implemented as a logical delete (marking as deleted),
// or by rewriting column files. In this version 0.0, we simulate deletion.
class DataDeleter {
public:
//     Deletes a row from the relation based on primary key value
//    bool deleteByPK(Relation* relation, const ColVal& pkValue);
//
//    // Deletes a specific row from the relation
//    bool deleteRow(Relation* relation, Row* row);
//
//    // Marks a row as deleted (soft delete)
////    bool markRowDeleted(Relation* relation, Row* row);
//
//    // Physically removes deleted rows from storage (cleanup)
//    bool purgeDeletedRows(Relation* relation);
//
//    //SOFT DELETE
//
//    bool DataDeleter::deleteRow(Relation* relation, const std::vector<std::string>& primaryKeyValues);

    static bool deleteRow(Relation* relation, const ColVal& pkVal);
};
//};

#endif // DATADELETER_H
