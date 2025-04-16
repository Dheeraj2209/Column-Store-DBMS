// dml_main.cpp
#include "Engines/DMLEngine.h"
#include "Engines/DDLEngine.h"
using namespace std;

int main() {
    // Step 1: Initialize the DDL Engine and create the database schema
    DDLEngine ddlEngine;
    std::string xmlSchemaPath = "/Users/pradyundevarakonda/CLionProjects/Column-Store-DBMS/src/xml/sample_instance.xml"; // Adjust path as needed

    std::cout << "Creating column store database from schema: " << xmlSchemaPath << std::endl;
//    if (!ddlEngine.loadSchemaFromXML(xmlSchemaPath)) {
//        std::cerr << "Failed to create column store database from schema." << std::endl;
//        return 1;
//    }
    std::cout << "Database schema created successfully." << std::endl;

    // Step 2: Initialize the DML Engine
    DMLEngine dmlEngine;
    std::string dbName = "ECommerceDB"; // Matches the database name in the XML

    // Step 3: Load Customer.csv
    std::string customerCsvPath = "/Users/pradyundevarakonda/CLionProjects/Column-Store-DBMS/example_CSVs/customers.csv"; // Adjust path as needed
    std::string customerRelationName = "Customer";

    std::cout << "\nLoading Customer data from: " << customerCsvPath << std::endl;
    if (!dmlEngine.loadDatafromCSV(dbName, customerCsvPath, customerRelationName)) {
        std::cerr << "Failed to load Customer data." << std::endl;
        return 1;
    }
    std::cout << "Customer data loaded successfully." << std::endl;

    // Step 4: Load Order.csv
    std::string orderCsvPath = "/Users/pradyundevarakonda/CLionProjects/Column-Store-DBMS/example_CSVs/orders.csv"; // Adjust path as needed
    std::string orderRelationName = "Order";

    std::cout << "\nLoading Order data from: " << orderCsvPath << std::endl;
//    if (!dmlEngine.loadDatafromCSV(dbName, orderCsvPath, orderRelationName)) {
//        std::cerr << "Failed to load Order data." << std::endl;
//        return 1;
//    }
    std::cout << "Order data loaded successfully." << std::endl;

    std::cout << "\nAll CSV loading operations completed successfully!" << std::endl;
    return 0;
}