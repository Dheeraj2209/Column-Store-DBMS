//
// Created by Pradyun Devarakonda on 12/03/25.
//
#ifndef DATAMANIPULATOR_HPP
#define DATAMANIPULATOR_HPP

#include "../include/external_includes.h"
#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"
#include "../Data_Objects/ColVal.hpp"
#include "../Data_Objects/Table.hpp"
#include "../Data_Objects/Row.hpp"
#include <vector>
#include <string>

// DataManipulator is responsible for updating data in a relation.
// In a column-store, an update can be complicated; for this version 0.0,
// we simulate an update operation.
class DataManipulator {
public:
    // Updates a tuple (row) in a given relation using newData.
    // newData is a vector of strings representing new values for each attribute,
    // in the same order as relation->getCAttributes().
    // Returns true on success.
    bool updateTuple(Relation* relation, int rowIndex, const std::vector<std::string>& newData);
    bool updateTuple(Relation* relation, Row* row);
    bool updateRow(Relation* relation, Row* row);
//    bool deleteRow(Relation* relation, const std::vector<std::string>& primaryKeyValues);

};

#endif // DATAMANIPULATOR_HPP
