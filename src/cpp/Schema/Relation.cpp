//
// Created by Pradyun Devarakonda on 11/03/25.
//

#include "Relation.h"
#include "CAttribute.h"
#include "Database.h"

// ---------- Relation Implementation ----------

std::map<std::string, CAttribute*> Relation::getCAttributes() const {
    return cattributes;
}
std::string Relation::getName() const {
    return this->name; // Return the name of the relation
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
bool Relation::addCAttribute(const CAttribute* attribute) {
    if (cattributes.find(attribute->name) != cattributes.end()) {
        std::cerr << "Error: Attribute " << attribute->name << " already exists in relation.\n";
        return false;
    }
    cattributes[attribute->name] = new CAttribute(attribute->name, attribute->type, attribute->isNullable, attribute->isUnique);
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

void Relation::setName(const std::string& name) {
    this->name = name;
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
std::map<string,PrimaryKeyConstraint*> Relation::getpks() {
    return pks;
}
std::map<string,ForeignKeyConstraint*> Relation::getfks() {
    return fks;
}
std::map<string,UniqueKeyConstraint*> Relation::getuks() {
    return uks;
}
std::string Relation::getDBName() const {
    return this->database->getName();
}

int Relation::getNumRows() {
    // Implement logic to count the number of rows in the relation
    // This is a placeholder implementation
    auto basepath = "../Databases/" + this->getDBName() + "/" + this->getName();
    auto pk = this->getPrimaryKey();
    auto pkattr = pk.attribute;
    auto pkattrpath = basepath + "/" + pkattr->getName() + ".dat";
    std::ifstream file(pkattrpath, std::ios::binary);
    int count = 0;
    while (file) {
//        file.read(reinterpret_cast<char *>(&count), sizeof(count));
           if(pkattr->getType() == "int"){
            int64_t value;
            file.read(reinterpret_cast<char *>(&value), sizeof(value));
            }
        else if(pkattr->getType() == "float"){
            double value;
            file.read(reinterpret_cast<char *>(&value), sizeof(value));
        }
        else{
            size_t len;
            file.read(reinterpret_cast<char *>(&len), sizeof(len));
            std::string value(len, '\0');
            file.read(&value[0], len);
        }
        count++;
    }

    return count;
}

// Destructor
Relation::~Relation() {
    // Destructor implementation
}