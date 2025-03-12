#include "DDLEngine.h"
#include <tinyxml2.h>
#include <iostream>

using namespace tinyxml2;

Database DDLEngine::loadSchemaFromXML(const std::string& xmlFilePath) {
    Database db(xmlFilePath);
    
    XMLDocument doc;
    if (doc.LoadFile(xmlFilePath.c_str()) != XML_SUCCESS) {
        std::cerr << "Failed to load XML file: " << xmlFilePath << std::endl;
        return db;
    }
    
    // Expected Root Element: <ColumnStoreSchema>
    XMLElement* root = doc.RootElement();
    if (!root) {
        std::cerr << "Invalid XML: No root element." << std::endl;
        return db;
    }
    
    // Parse the <Database> element.
    XMLElement* dbElement = root->FirstChildElement("Database");
    if (!dbElement) {
        std::cerr << "Invalid XML: No <Database> element found." << std::endl;
        return db;
    }
    
    const char* dbName = dbElement->Attribute("name");
    if (dbName)
        db.name = dbName;
    else
        std::cerr << "Database name attribute missing." << std::endl;
    
    // Parse Relations 
    XMLElement* relationsElement = dbElement->FirstChildElement("Relations");
    if (relationsElement) {
        for (XMLElement* relationElem = relationsElement->FirstChildElement("Relation");
             relationElem;
             relationElem = relationElem->NextSiblingElement("Relation")) {
            
            Relation* rel = new Relation();
            const char* relName = relationElem->Attribute("name");
            if (relName)
                rel->name = relName;
            
            // Parse Attributes
            XMLElement* attributesElem = relationElem->FirstChildElement("Attributes");
            if (attributesElem) {
                for (XMLElement* attrElem = attributesElem->FirstChildElement("Attribute");
                     attrElem;
                     attrElem = attrElem->NextSiblingElement("Attribute")) {
                    
                    const char* attrName = attrElem->Attribute("name");
                    const char* attrType = attrElem->Attribute("type");
                    bool isNullable = true, isUnique = false;
                    attrElem->QueryBoolAttribute("isNullable", &isNullable);
                    attrElem->QueryBoolAttribute("isUnique", &isUnique);
                    
                    if (attrName && attrType) {
                        rel->attributes.emplace_back(attrName, attrType, isNullable, isUnique);
                    }
                }
            }
            
            // Parse PKs
            XMLElement* pkElem = relationElem->FirstChildElement("PrimaryKey");
            if (pkElem) {
                for (XMLElement* attrRef = pkElem->FirstChildElement("AttributeRef");
                     attrRef;
                     attrRef = attrRef->NextSiblingElement("AttributeRef")) {
                    const char* refName = attrRef->Attribute("name");
                    if (refName)
                        rel->primaryKey.attributeRefs.push_back(refName);
                }
            }
            
            db.schemaElements.push_back(rel);
        }
    }
    
    // Parse FKs as Constraints
    XMLElement* fkElement = dbElement->FirstChildElement("ForeignKeys");
    if (fkElement) {
        for (XMLElement* fkElem = fkElement->FirstChildElement("ForeignKey");
             fkElem;
             fkElem = fkElem->NextSiblingElement("ForeignKey")) {
            
            Constraint* cons = new Constraint();
            cons->type = "ForeignKey";
            const char* fkName = fkElem->Attribute("name");
            if (fkName)
                cons->name = fkName;
            
            XMLElement* parentElem = fkElem->FirstChildElement("Parent");
            if (parentElem) {
                const char* pTable = parentElem->Attribute("table");
                const char* pColumn = parentElem->Attribute("column");
                if (pTable) cons->parentTable = pTable;
                if (pColumn) cons->parentColumn = pColumn;
            }
            
            XMLElement* childElem = fkElem->FirstChildElement("Child");
            if (childElem) {
                const char* cTable = childElem->Attribute("table");
                const char* cColumn = childElem->Attribute("column");
                if (cTable) cons->childTable = cTable;
                if (cColumn) cons->childColumn = cColumn;
            }
            
            db.schemaElements.push_back(cons);
        }
    }
    
    // Parse Unique Constraints as Constraints 
    XMLElement* ucElement = dbElement->FirstChildElement("UniqueConstraints");
    if (ucElement) {
        for (XMLElement* ucElem = ucElement->FirstChildElement("UniqueConstraint");
             ucElem;
             ucElem = ucElem->NextSiblingElement("UniqueConstraint")) {
            
            Constraint* cons = new Constraint();
            cons->type = "Unique";
            const char* ucName = ucElem->Attribute("name");
            const char* relationAttr = ucElem->Attribute("relation");
            if (ucName)
                cons->name = ucName;
            if (relationAttr)
                cons->relation = relationAttr;
            
            for (XMLElement* attrRef = ucElem->FirstChildElement("AttributeRef");
                 attrRef;
                 attrRef = attrRef->NextSiblingElement("AttributeRef")) {
                const char* refName = attrRef->Attribute("name");
                if (refName)
                    cons->attributeRefs.push_back(refName);
            }
            
            db.schemaElements.push_back(cons);
        }
    }
    
    // Parse Views 
    XMLElement* viewsElement = dbElement->FirstChildElement("Views");
    if (viewsElement) {
        for (XMLElement* viewElem = viewsElement->FirstChildElement("View");
             viewElem;
             viewElem = viewElem->NextSiblingElement("View")) {
            View* view = new View();
            const char* viewName = viewElem->Attribute("name");
            const char* viewQuery = viewElem->GetText(); // Assume view definition is text content
            if (viewName)
                view->name = viewName;
            if (viewQuery)
                view->query = viewQuery;
            db.schemaElements.push_back(view);
        }
    }
    
    return db;
}

using namespace tinyxml2;

bool DDLEngine::createColumnStoreDBfromXMLSchema(const std::string& xmlFilePath) {
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

