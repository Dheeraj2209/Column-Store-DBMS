#include <cassert>
#include <iostream>
#include "../Engines/DataLoader.h"
#include "../Engines/DataManipulator.hpp"
#include "../Engines/DataDeleter.h"
#include "../Schema/Database.h"

void testDataOperations() {
    // Create test database and relation
    Database db;
    db.setName("TestDB");

    Relation* relation = new Relation();
    relation->setName("TestTable");

    // Add attributes
    CAttribute* idAttr = new CAttribute("id", "integer", false, true, true);
    CAttribute* nameAttr = new CAttribute("name", "string", false, false, false);

    relation->addCAttribute(idAttr);
    relation->addCAttribute(nameAttr);

    PrimaryKey pk;
    pk.attribute = idAttr;
    relation->setPrimaryKey(pk);

    db.addRelation(relation);

    // Test DataLoader
    DataLoader loader;
    bool loadResult = loader.loadDataFromCSV(&db, "TestTable", "test_data.csv");
    assert(loadResult && "Data loading should succeed");

    // Test DataManipulator
    DataManipulator manipulator;
    Row* row = new Row(relation);
    row->addColVal(new ColVal(idAttr, 1));
    row->addColVal(new ColVal(nameAttr, "Updated Name"));

    bool updateResult = manipulator.updateTuple(relation, row);
    assert(updateResult && "Update should succeed");

    // Test DataDeleter
    DataDeleter deleter;
    bool deleteResult = deleter.deleteRow(relation, row);
    assert(deleteResult && "Delete should succeed");

    std::cout << "All data operation tests passed!" << std::endl;
}

int main() {
    testDataOperations();
    return 0;
}