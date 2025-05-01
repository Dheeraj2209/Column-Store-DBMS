 // print_main.cpp
//
// #include "Engines/DDLEngine.h"
// using namespace std;
//
// int main() {
//     // Step 2: Initialize the DML Engine
//     DMLEngine dmlEngine;
//     string dbName = "ECommerceDB_main"; // Matches the database name in the XML
//
//     dmlEngine.printTable(dbName, "Order");
//     return 0;
// }

#include "Engines/DDLEngine.h"
#include <iostream>
#include "Engines/DMLEngine.h"
int main(int argc, char** argv) {
 if (argc != 3) {
  std::cerr << "Usage: " << argv[0] << " <DatabaseName> <RelationName>\n";
  return 1;
 }

 std::string dbName      = argv[1];
 std::string relationName = argv[2];

 // Initialize and load the DML engine (assumes you have a setter or constructor)
 DMLEngine dmlEngine;
// dmlEngine.setDatabaseName(dbName);

 // Print the table
 if (!dmlEngine.printTable(dbName, relationName)) {
  std::cerr << "Failed to print table `" << relationName << "` in database `" << dbName << "`\n";
  return 1;
 }

 return 0;
}
