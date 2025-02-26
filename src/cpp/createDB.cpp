#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <tinyxml2.h>
#include "createDB.h"

namespace fs = std::filesystem;
using namespace tinyxml2;

bool createColumnStoreDB(const std::string& xmlFilePath) {
    // Parse XML file
    XMLDocument doc;
    if (doc.LoadFile(xmlFilePath.c_str()) != XML_SUCCESS) {
        std::cerr << "Failed to load XML file: " << xmlFilePath << std::endl;
        return false;
    }

    XMLElement* root = doc.RootElement();
    XMLElement* databaseElement = root->FirstChildElement("Database");
    if (!databaseElement) {
        std::cerr << "Invalid XML: No <Database> element found." << std::endl;
        return false;
    }

    std::string dbName = databaseElement->Attribute("name");
    fs::path dbPath = fs::path("../../Databases") / dbName;
    fs::create_directories(dbPath);

    // Process relations
    XMLElement* relationsElement = databaseElement->FirstChildElement("Relations");
    if (relationsElement) {
        for (XMLElement* relation = relationsElement->FirstChildElement("Relation"); relation; relation = relation->NextSiblingElement("Relation")) {
            std::string relationName = relation->Attribute("name");
            fs::path relationPath = dbPath / relationName;
            fs::create_directories(relationPath);

            // Process attributes
            XMLElement* attributesElement = relation->FirstChildElement("Attributes");
            if (attributesElement) {
                for (XMLElement* attribute = attributesElement->FirstChildElement("Attribute"); attribute; attribute = attribute->NextSiblingElement("Attribute")) {
                    std::string attrName = attribute->Attribute("name");
                    fs::path datFilePath = relationPath / (attrName + ".dat");
                    std::ofstream datFile(datFilePath);
                    if (!datFile) {
                        std::cerr << "Failed to create file: " << datFilePath << std::endl;
                    }
                }
            }
        }
    }

    // Process foreign keys
    XMLElement* foreignKeysElement = databaseElement->FirstChildElement("ForeignKeys");
    if (foreignKeysElement) {
        fs::path fkFilePath = dbPath / "foreign_keys.txt";
        std::ofstream fkFile(fkFilePath);
        if (!fkFile) {
            std::cerr << "Failed to create foreign keys file." << std::endl;
            return false;
        }

        for (XMLElement* foreignKey = foreignKeysElement->FirstChildElement("ForeignKey"); foreignKey; foreignKey = foreignKey->NextSiblingElement("ForeignKey")) {
            std::string fkName = foreignKey->Attribute("name");
            XMLElement* parent = foreignKey->FirstChildElement("Parent");
            XMLElement* child = foreignKey->FirstChildElement("Child");
            if (parent && child) {
                fkFile << "FK: " << fkName << " - "
                       << "Parent: " << parent->Attribute("table") << "(" << parent->Attribute("column") << ")"
                       << " -> "
                       << "Child: " << child->Attribute("table") << "(" << child->Attribute("column") << ")"
                       << std::endl;
            }
        }
    }
    return true;
}

// int main(int argc, char* argv[]) {
//     if (argc != 2) {
//         std::cerr << "Usage: " << argv[0] << " <XML file path>" << std::endl;
//         return 1;
//     }
//     createColumnStoreDB(argv[1]);
//     return 0;
// }
