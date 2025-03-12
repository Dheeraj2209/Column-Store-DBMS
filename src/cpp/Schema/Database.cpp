//
// Created by Pradyun Devarakonda on 11/03/25.
//

#include "Database.h"

Database::Database(){}
Database::Database(const std::string& xmlFilePath){
  this->xmlFilePath = xmlFilePath;
}
// ---------- Database Implementation ----------
bool Database::create() const {
    // Create the main database directory under ../../Databases/DatabaseName.
    fs::path basePath = fs::path("../../Databases") / name;
    try {
        fs::create_directories(basePath);
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error creating database directory (" << name << "): " << e.what() << std::endl;
        return false;
    }

    // For each schema element, call its create() method.
    for (const Schema_Element *elem : schemaElements) {
        if (!elem->create(basePath)) {
            std::cerr << "Failed to create schema element: " << elem->name << std::endl;
            return false;
        }
    }
    return true;
}

Database::~Database() {
    // Clean up allocated Schema_Element pointers.
    for (Schema_Element *elem : schemaElements) {
        delete elem;
    }
}
