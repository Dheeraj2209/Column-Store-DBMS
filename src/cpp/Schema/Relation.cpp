//
// Created by Pradyun Devarakonda on 11/03/25.
//

#include "Relation.h"

// ---------- Relation Implementation ----------

std::map<std::string, CAttribute*> Relation::getCAttributes() const {
    return cattributes;
}
PrimaryKey Relation::getPrimaryKey() const {
    return primaryKey;
}
bool Relation::setCAttributes(const std::map<std::string, CAttribute*>& attributes) {
    cattributes = attributes;
    return true;
}
bool Relation::setPrimaryKey(const PrimaryKey& primaryKey) {
    this->primaryKey = primaryKey;
    return true;
}
bool Relation::addCAttribute(const CAttribute& attribute) {
    if (cattributes.find(attribute.name) != cattributes.end()) {
        std::cerr << "Error: Attribute " << attribute.name << " already exists in relation.\n";
        return false;
    }
    cattributes[attribute.name] = new CAttribute(attribute);
    return true;
}
bool Relation::removeCAttribute(const std::string& attributeName) {
    if (cattributes.find(attributeName) == cattributes.end()) {
        std::cerr << "Error: Attribute " << attributeName << " not found in relation.\n";
        return false;
    }
    cattributes.erase(attributeName);
    return true;
}
CAttribute* Relation::getCAttribute(const std::string& attributeName) {
    if (cattributes.find(attributeName) == cattributes.end()) {
        std::cerr << "Error: Attribute " << attributeName << " not found in relation.\n";
        return NULL;
    }
    return cattributes[attributeName];
}


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
//    for (const CAttribute* attr : cattributes) {
//        fs::path filePath = relationPath / (attr->name + ".dat");
//        std::ofstream outFile(filePath);
//        if (!outFile) {
//            std::cerr << "Failed to create attribute file: " << filePath << std::endl;
//            return false;
//        }
//    }
    for (auto &pair : cattributes) {
        fs::path filePath = relationPath / (pair.first + ".dat");
        std::ofstream outFile(filePath);
        if (!outFile) {
            std::cerr << "Failed to create attribute file: " << filePath << std::endl;
            return false;
        }
    }
    return true;
}
Relation::~Relation() {}