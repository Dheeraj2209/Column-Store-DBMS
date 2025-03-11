#include "ColumnStoreDB.h"
#include <fstream>
#include <iostream>

// ---------- Attribute Implementation ----------
Attribute::Attribute(const std::string& name, const std::string& type, bool isNullable, bool isUnique)
    : name(name), type(type), isNullable(isNullable), isUnique(isUnique) {}

// ---------- Relation Implementation ----------
bool Relation::create(const fs::path &basePath) const {
    // Create a directory for the relation under the database base path.
    fs::path relationPath = basePath / name;
    try {
        fs::create_directories(relationPath);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error creating relation directory (" << name << "): " << e.what() << std::endl;
        return false;
    }
    
    // Create a .dat file for each attribute.
    for (const Attribute &attr : attributes) {
        fs::path filePath = relationPath / (attr.name + ".dat");
        std::ofstream outFile(filePath);
        if (!outFile) {
            std::cerr << "Failed to create attribute file: " << filePath << std::endl;
            return false;
        }
    }
    return true;
}

// ---------- Constraint Implementation ----------
bool Constraint::create(const fs::path &basePath) const {
    // Append constraint information to a file "constraints.txt" in the database directory.
    fs::path constraintsFile = basePath / "constraints.txt";
    std::ofstream outFile(constraintsFile, std::ios::app);
    if (!outFile) {
        std::cerr << "Failed to open constraints file: " << constraintsFile << std::endl;
        return false;
    }
    if (type == "ForeignKey") {
        outFile << "ForeignKey: " << name << " - Parent: " << parentTable << "(" << parentColumn << ")"
                << " -> Child: " << childTable << "(" << childColumn << ")" << std::endl;
    } else if (type == "Unique") {
        outFile << "UniqueConstraint: " << name << " on Relation: " << relation << " Attributes: ";
        for (const std::string &attr : attributeRefs) {
            outFile << attr << " ";
        }
        outFile << std::endl;
    }
    return true;
}

// ---------- View Implementation ----------
bool View::create(const fs::path &basePath) const {
    // Create a file for the view definition.
    fs::path viewFile = basePath / (name + "_view.txt");
    std::ofstream outFile(viewFile);
    if (!outFile) {
        std::cerr << "Failed to create view file: " << viewFile << std::endl;
        return false;
    }
    outFile << "View Query: " << query << std::endl;
    return true;
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
