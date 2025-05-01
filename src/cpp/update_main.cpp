// dml_main.cpp

#include "Engines/DDLEngine.h"
#include "Engines/DMLEngine.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " <dbName> <relationName> <oldKey> <newVal1> <newVal2> ... (column values in alphabetical order)\n";
        return 1;
    }

    string dbName       = argv[1];
    string relationName = argv[2];
    string oldKey       = argv[3];

    vector<string> newValues;
    for (int i = 4; i < argc; ++i) {
        newValues.push_back(argv[i]);
    }

    DMLEngine dmlEngine;

    // Optional: ensure DB and relation exist
    Database* db = dmlEngine.getDatabase(dbName);
    if (!db) {
        cerr << "Database \"" << dbName << "\" not found.\n";
        return 1;
    }

    Relation* rel = db->getRelation(relationName);
    if (!rel) {
        cerr << "Relation \"" << relationName << "\" not found in database \"" << dbName << "\".\n";
        return 1;
    }

    cout << "Updating row in relation \"" << relationName << "\" with key \"" << oldKey << "\"...\n";

    if (!dmlEngine.updateRow(dbName, relationName, oldKey, newValues)) {
        cerr << "Row update failed.\n";
        return 1;
    }

    cout << "Row updated successfully!\n";
    return 0;
}
