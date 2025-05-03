#include <iostream>
#include <string>
#include <cstdlib>
#include "Engines/DMLEngine.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <DatabaseName> <RelationName> <KeyValue>\n";
        return 1;
    }

    std::string dbName = argv[1];
    std::string relationName = argv[2];
    int keyValue;

    try {
        keyValue = std::stoi(argv[3]);
    } catch (const std::exception& e) {
        std::cerr << "Invalid key value: " << argv[3] << "\n";
        return 1;
    }

    DMLEngine engine;
    Database* db = engine.getDatabase(dbName);
    if (!db) {
        std::cerr << "Database not found: " << dbName << "\n";
        return 1;
    }

    bool ok = engine.row_undelete(dbName, relationName, keyValue);
    if (!ok) {
        std::cerr << "Undeletion failed on " << relationName
                  << " where key=" << keyValue << "\n";
        return 1;
    }

    std::cout << "Undeletion succeeded on " << relationName
              << " where key=" << keyValue << "\n";
    return 0;
}
