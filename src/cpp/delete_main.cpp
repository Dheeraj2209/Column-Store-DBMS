//#include <iostream>
//#include "Engines/DMLEngine.h"
//#include "Data_Objects/ColVal.hpp"
//#include "Schema/CAttribute.h"
//
//int main() {
//    DMLEngine engine;
//    auto dbName = "ECommerceDB_main";
//   Database* db = engine.getDatabase(dbName);
//   int val = 7;
//    if (!engine.row_delete(dbName,"Customer", val)) {
//        std::cerr<<"Deletion failed\n";
//        return 1;
//    }
//    std::cout<<"Deletion succeeded.\n";
//    return 0;
//}
#include <iostream>
#include <string>
#include <cstdlib>
#include "Engines/DMLEngine.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <DatabaseName> <RelationName> <KeyValue>\n";
        return 1;
    }

    std::string dbName      = argv[1];
    std::string relationName = argv[2];
    // assuming key is integer; adjust stoi → stoll if you use 64-bit keys
    int keyValue;
    try {
        keyValue = std::stoi(argv[3]);
    } catch (const std::exception& e) {
        std::cerr << "Invalid key value: " << argv[3] << "\n";
        return 1;
    }

    DMLEngine engine;
    // Load or select the database; adjust if your engine API differs
    Database* db = engine.getDatabase(dbName);
    if (!db) {
        std::cerr << "Database not found: " << dbName << "\n";
        return 1;
    }

    bool ok = engine.row_delete(dbName, relationName, keyValue);
    if (!ok) {
        std::cerr << "Deletion failed on " << relationName
                  << " where key=" << keyValue << "\n";
        return 1;
    }

    std::cout << "Deletion succeeded on " << relationName
              << " where key=" << keyValue << "\n";
    return 0;
}
