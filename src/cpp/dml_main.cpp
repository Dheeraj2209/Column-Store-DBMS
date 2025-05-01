//  // dml_main.cpp
//
//  #include "Engines/DDLEngine.h"
//  using namespace std;
//
//  int main() {
//      // Step 1: Initialize the DDL Engine and create the database schema
// //     DDLEngine ddlEngine;
// //     std::string xmlSchemaPath = "/Users/pradyundevarakonda/CLionProjects/Column-Store-DBMS/src/xml/sample_instance.xml"; // Adjust path as needed
// //
// //     std::cout << "Creating column store database from schema: " << xmlSchemaPath << std::endl;
// // //    if (!ddlEngine.loadSchemaFromXML(xmlSchemaPath)) {
// // //        std::cerr << "Failed to create column store database from schema." << std::endl;
// // //        return 1;
// // //    }
// //     std::cout << "Database schema created successfully." << std::endl;
//
//      // Step 2: Initialize the DML Engine
//      DMLEngine dmlEngine;
//
// //     if (!DMLEngine::init()) {
// //            std::cerr << "Failed to initialize DML engine." << std::endl;
// //            return 1;
// //        }
//      std::string dbName = "ECommerceDB_main"; // Matches the database name in the XML
//      // std::string dbName = "ECommerceDB";
//      //
//      // Step 3: Load Customer.csv
//      std::string customerCsvPath = "../../example_CSVs/customers3.csv"; // Adjust path as needed
//      std::string customerRelationName = "Customer";
//
//      std::cout << "\nLoading Customer data from: " << customerCsvPath << std::endl;
//      if (!dmlEngine.loadDatafromCSV(dbName, customerCsvPath, customerRelationName)) {
//      // if (!dmlEngine.loadCSVData(dbName, customerCsvPath, customerRelationName)) {
//          std::cerr << "Failed to load Customer data." << std::endl;
//          return 1;
//      }
//      std::cout << "Customer data loaded successfully." << std::endl;
//
//      // Step 4: Load Order.csv
//  //     std::string orderCsvPath ="../../example_CSVs/orders2.csv"; // Adjust path as needed
//  //     std::string orderRelationName = "Order";
//  //
//  //     std::cout << "\nLoading Order data from: " << orderCsvPath << std::endl;
//  // if (!dmlEngine.loadDatafromCSV(dbName, orderCsvPath, orderRelationName)) {
//  //     std::cerr << "Failed to load Order data." << std::endl;
//  //     return 1;
//  // }
//  //     std::cout << "Order data loaded successfully." << std::endl;
//
//  std::cout << "\nAll CSV loading operations completed successfully!" << std::endl;
//      return 0;
//  }


// dml_main.cpp

#include "Engines/DDLEngine.h"
#include "Engines/DMLEngine.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <DatabaseName> <RelationName> <CSVFilePath>" << endl;
        return 1;
    }

    string dbName = argv[1];
    string relationName = argv[2];
    string csvPath = argv[3];

    cout << "\nInitializing DML Engine..." << endl;
    DMLEngine dmlEngine;

    cout << "\nLoading data from CSV:\n"
         << "Database: " << dbName << "\n"
         << "Relation: " << relationName << "\n"
         << "CSV File: " << csvPath << "\n";

    if (!dmlEngine.loadDatafromCSV(dbName, csvPath, relationName)) {
        cerr << "Failed to load data from CSV." << endl;
        return 1;
    }

    cout << "Data loaded successfully into relation '" << relationName << "' of database '" << dbName << "'." << endl;
    return 0;
}
