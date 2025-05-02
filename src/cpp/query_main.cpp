#include <iostream>
#include <string>
#include <cstdlib>
#include "Engines/DMLEngine.h"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "argc = " << argc << "\n";
        std::cerr << "Usage: " << argv[0] << " <DatabaseName> <RelationName> '<CommaSeparatedColumnNames>' '<CommaSeparatedConstraints>'\n"
        << "Constraint: <ColumnName> <Operator> <Literal>\n";
        return 1;
    }

    std::string dbName      = argv[1];
    std::string relationName = argv[2];
    std::string columnNames = argv[3]; // e.g., "col1,col2,col3"
    columnNames = columnNames.substr(1, columnNames.length() - 2); // remove quotes
    std::string constraints = argv[4]; // e.g., "col1=5,col2>10"
    constraints = constraints.substr(1, constraints.length() - 2); // remove quotes
    // assuming key is integer; adjust stoi → stoll if you use 64-bit keys

    DMLEngine engine;
    // Load or select the database; adjust if your engine API differs
    Database* db = engine.getDatabase(dbName);
    if (!db) {
        std::cerr << "Database not found: " << dbName << "\n";
        return 1;
    }

    bool ok = engine.run_query(dbName, relationName, columnNames, constraints);
    if (!ok) {
        std::cerr << "Query failed on " << relationName << "\n";
        return 1;
    }

    std::cout << "Query succeeded on " << relationName << "\n";
    return 0;
}
