#include "DMLEngine.h"

int main() {
    DMLEngine dmlEngine;

    // Initialize the engine
    if (!dmlEngine.init()) {
        std::cerr << "Failed to initialize DMLEngine." << std::endl;
        return 1;
    }

    // Test deleting a row
    std::string dbName = "ECommerceDB_main"; // Adjust as needed
    std::string relationName = "Customer";
    std::vector<std::string> primaryKeyValues = {"123"}; // Example primary key value

    if (dmlEngine.deleteRow(dbName, relationName, primaryKeyValues)) {
        std::cout << "Row deleted successfully." << std::endl;
    } else {
        std::cerr << "Failed to delete row." << std::endl;
    }

    return 0;
}