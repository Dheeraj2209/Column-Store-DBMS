#include <cassert>
#include <iostream>
#include "../Engines/DataLoader.h"
#include "../Engines/DDLEngine.h"

void testDataLoading() {
    // First create a database
    std::string xmlPath = "../../src/xml/sample_instance.xml";
    Database db = DDLEngine::loadSchemaFromXML(xmlPath);

    // Test CSV loading
    DataLoader loader;
    bool result = loader.loadDataFromCSV(&db, "Customer", "../../example_CSVs/customers.csv");
    assert(result && "Data loading should succeed");

    // Test loading orders
    result = loader.loadDataFromCSV(&db, "Order", "../../example_CSVs/orders.csv");
    assert(result && "Order data loading should succeed");

    std::cout << "Data loading tests passed!" << std::endl;
}

int main() {
    testDataLoading();
    return 0;
}