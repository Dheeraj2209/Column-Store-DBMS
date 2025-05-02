//// insert_row_example.cpp
//
//#include <iostream>
//#include <vector>
//#include "Schema/Database.h"
//#include "Engines/DDLEngine.h"
//#include "Engines/DMLEngine.h"   // assume DMLEngine has insertRow(...)
//#include "CustomTypes/Date_DDMMYYYY_Type.h"
//
//int main(int argc, char** argv) {
//    // 1) load schema
////    std::string schemaPath = "../../Databases/ECommerceDB/ECommerceDB_schema.xml";
////    Database db;
////    DDLEngine ddl;
////    if (!ddl.loadSchemaFromXML(schemaPath, db)) {
////        std::cerr << "Failed to load schema from " << schemaPath << "\n";
////        return 1;
////    }
////    std::cout << "Schema for '" << db.getName() << "' loaded successfully.\n";
//
//    // 2) set up DML engine
//    DMLEngine dml;
//    Database* db = dml.getDatabase("ECommerceDB_main");
//    if (!db) {
//        std::cerr << "Database not found.\n";
//        return 1;
//    }
//
//    // 3) prepare a new tuple for the CUSTOMER relation
//    //    the CSV order is [ CustomerID, Name, Email, RegistrationDate ]
//    std::vector<std::string> newCustomer {
//        "5",                       // CustomerID (integer)
//        "charlie@funnyfilms.com",  // Email
//        "Charlie Chaplin",         // Name
//    };
//
//    // 4) call insertRow, which under the hood:
//    //    - wraps these strings in a Row/ColVal
//    //    - checks PK/UK/FK via ConstraintValidator
//    //    - appends binary to the .dat column files
//    bool ok = dml.insertRow("Customer", newCustomer,db);
//    if (!ok) {
//        std::cerr << "Insert failed due to constraint or IO error.\n";
//        return 2;
//    }
//
//    std::cout << "Inserted new customer row successfully.\n";
//    return 0;
//}

#include <iostream>
#include <vector>
#include "Schema/Database.h"
#include "Engines/DDLEngine.h"
#include "Engines/DMLEngine.h"

int main(int argc, char** argv) {
    // Check minimum argument count
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <DatabaseName> <RelationName> <value1> <value2> ... (column values in alphabetical order)\n";
        return 1;
    }

    std::string dbName = argv[1];
    std::string relationName = argv[2];
    std::vector<std::string> values;

    for (int i = 3; i < argc; ++i) {
        values.push_back(argv[i]);
    }

    // 1) Set up DML engine and get database
    DMLEngine dml;
    Database* db = dml.getDatabase(dbName);
    if (!db) {
        std::cerr << "Database '" << dbName << "' not found.\n";
        return 2;
    }

    // 2) Try to insert row into given relation
    bool ok = dml.insertRow(relationName, values, db);
    if (!ok) {
        std::cerr << "Insert failed due to constraint or IO error.\n";
        return 3;
    }

    std::cout << "Inserted row into relation '" << relationName << "' successfully.\n";
    return 0;
}
