#include <cassert>
#include <iostream>
#include "../Engines/DDLEngine.h"

void testDatabaseCreation() {
    std::string xmlPath = "../../src/xml/sample_instance.xml";

    // Test database creation
    Database db = DDLEngine::loadSchemaFromXML(xmlPath);
    assert(!db.getName().empty() && "Database name should not be empty");

    // Test relation creation
    auto relations = db.getRelations();
    assert(!relations.empty() && "Database should have relations");

    // Test Customer relation
    auto customerRel = db.getRelation("Customer");
    assert(customerRel != nullptr && "Customer relation should exist");

    // Test attributes
    auto attributes = customerRel->getCAttributes();
    assert(attributes.find("CustomerID") != attributes.end() && "CustomerID attribute should exist");

    std::cout << "Database creation tests passed!" << std::endl;
}

int main() {
    testDatabaseCreation();
    return 0;
}