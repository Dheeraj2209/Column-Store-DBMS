#include "DDLEngine.h"
#include <tinyxml2.h>
#include <iostream>

using namespace tinyxml2;

bool DDLEngine::init() {
  //let's use the global variables declared in the header file
//    meta_metadata_path = fs::path("../../Databases") / "meta_metadata.json";
//    meta_metadata_file(meta_metadata_path, std::ios::app);
//    if (!meta_metadata_file) {
//        std::cerr << "Failed to create meta_metadata file." << std::endl;
//        return false;
//    }
//    return true;
//   meta_metadata_path = fs::path("../../Databases");
//    meta_metadata_file(meta_metadata_path, std::ios::app);
//    if (!meta_metadata_file) {
//        std::cerr << "Failed to create meta_metadata file." << std::endl;
//        return false;
//    }
    return true;
}
//Database DDLEngine::loadSchemaFromXML(const std::string& xmlFilePath) {
//    Database db(xmlFilePath);
//
//    XMLDocument doc;
//    if (doc.LoadFile(xmlFilePath.c_str()) != XML_SUCCESS) {
//        std::cerr << "Failed to load XML file: " << xmlFilePath << std::endl;
//        return db;
//    }
//
//    // Expected Root Element: <ColumnStoreSchema>
//    XMLElement* root = doc.RootElement();
//    if (!root) {
//        std::cerr << "Invalid XML: No root element." << std::endl;
//        return db;
//    }
//
//    // Parse the <Database> element.
//    XMLElement* dbElement = root->FirstChildElement("Database");
//    if (!dbElement) {
//        std::cerr << "Invalid XML: No <Database> element found." << std::endl;
//        return db;
//    }
//
//    const char* dbName = dbElement->Attribute("name");
//    if (dbName)
//        db.setName(dbName);
//    else
//        std::cerr << "Database name attribute missing." << std::endl;
//
//    // Parse Relations
//    XMLElement* relationsElement = dbElement->FirstChildElement("Relations");
//    if (relationsElement) {
//        for (XMLElement* relationElem = relationsElement->FirstChildElement("Relation");
//             relationElem;
//             relationElem = relationElem->NextSiblingElement("Relation")) {
//
//            Relation* rel = new Relation();
//            const char* relName = relationElem->Attribute("name");
//            if (relName)
//                rel->name = relName;
//
//            // Parse Attributes
//            XMLElement* attributesElem = relationElem->FirstChildElement("Attributes");
//            if (attributesElem) {
//                for (XMLElement* attrElem = attributesElem->FirstChildElement("Attribute");
//                     attrElem;
//                     attrElem = attrElem->NextSiblingElement("Attribute")) {
//
//                    const char* attrName = attrElem->Attribute("name");
//                    const char* attrType = attrElem->Attribute("type");
//                    bool isNullable = true, isUnique = false;
//                    attrElem->QueryBoolAttribute("isNullable", &isNullable);
//                    attrElem->QueryBoolAttribute("isUnique", &isUnique);
//
//                    if (attrName && attrType) {
//                        CAttribute attr = CAttribute(attrName, attrType, isNullable, isUnique);
//                        rel->addCAttribute(attr);
////                        rel->cattributes.emplace_back(attrName, attrType, isNullable, isUnique);
//                    }
//                }
//            }
//
//            // Parse PKs
//            XMLElement* pkElem = relationElem->FirstChildElement("PrimaryKey");
//            if (pkElem) {
//                for (XMLElement* attrRef = pkElem->FirstChildElement("AttributeRef");
//                     attrRef;
//                     attrRef = attrRef->NextSiblingElement("AttributeRef")) {
//                    const char* refName = attrRef->Attribute("name");
//                    if (refName){
//                         PrimaryKey pk;
//                         pk.attributeRefs.push_back(refName);
//                         rel->setPrimaryKey(pk);
////                        rel->primaryKey.attributeRefs.push_back(refName);
//                        }
//                }
//            }
//            db.addRelation(rel);
////            db.relations.push_back(rel);
//        }
//    }
//
//    // Parse FKs as Constraints
//    XMLElement* fkElement = dbElement->FirstChildElement("ForeignKeys");
//    if (fkElement) {
//        for (XMLElement* fkElem = fkElement->FirstChildElement("ForeignKey");
//             fkElem;
//             fkElem = fkElem->NextSiblingElement("ForeignKey")) {
//
//            Constraint* cons = new Constraint();
//            cons->type = "ForeignKey";
//            const char* fkName = fkElem->Attribute("name");
//            if (fkName)
//                cons->name = fkName;
//
//            XMLElement* parentElem = fkElem->FirstChildElement("Parent");
//            if (parentElem) {
//                const char* pTable = parentElem->Attribute("table");
//                const char* pColumn = parentElem->Attribute("column");
//                if (pTable) cons->parentTable = pTable;
//                if (pColumn) cons->parentColumn = pColumn;
//            }
//
//            XMLElement* childElem = fkElem->FirstChildElement("Child");
//            if (childElem) {
//                const char* cTable = childElem->Attribute("table");
//                const char* cColumn = childElem->Attribute("column");
//                if (cTable) cons->childTable = cTable;
//                if (cColumn) cons->childColumn = cColumn;
//            }
//            db.addConstraint(cons);
////            db.constraints.push_back(cons);
//        }
//    }
//
//    // Parse Unique Constraints as Constraints
//    XMLElement* ucElement = dbElement->FirstChildElement("UniqueConstraints");
//    if (ucElement) {
//        for (XMLElement* ucElem = ucElement->FirstChildElement("UniqueConstraint");
//             ucElem;
//             ucElem = ucElem->NextSiblingElement("UniqueConstraint")) {
//
//            Constraint* cons = new Constraint();
//            cons->type = "Unique";
//            const char* ucName = ucElem->Attribute("name");
//            const char* relationAttr = ucElem->Attribute("relation");
//            if (ucName)
//                cons->name = ucName;
//            if (relationAttr)
//                cons->relation = relationAttr;
//
//            for (XMLElement* attrRef = ucElem->FirstChildElement("AttributeRef");
//                 attrRef;
//                 attrRef = attrRef->NextSiblingElement("AttributeRef")) {
//                const char* refName = attrRef->Attribute("name");
//                if (refName)
//                    cons->attributeRefs.push_back(refName);
//            }
//            db.addConstraint(cons);
////            db.constraints.push_back(cons);
//        }
//    }
//
//    // Parse Views
//    XMLElement* viewsElement = dbElement->FirstChildElement("Views");
//    if (viewsElement) {
//        for (XMLElement* viewElem = viewsElement->FirstChildElement("View");
//             viewElem;
//             viewElem = viewElem->NextSiblingElement("View")) {
//            View* view = new View();
//            const char* viewName = viewElem->Attribute("name");
//            const char* viewQuery = viewElem->GetText(); // Assume view definition is text content
//            if (viewName)
//                view->name = viewName;
//            if (viewQuery)
//                view->query->setQuerystring(viewQuery);
//            db.addView(view);
//        }
//    }
//    //let's copy all the xml content and push it to a xml file Databases/<database_name>/<database_name>.xml
//    fs::path dbPath = fs::path("../../Databases") / db.getName();
//    fs::create_directories(dbPath);
//    fs::path xmlFilePath = dbPath / (db.getName() + ".xml");
//    std::ofstream xmlFile(xmlFilePath);
//    if (!xmlFile) {
//        std::cerr << "Failed to create XML file: " << xmlFilePath << std::endl;
//        return db;
//    }
//    doc.Print(xmlFile);
//    return db;
//    if(pushSchematoMeta_Metadata(db)){
//          cout << "Schema pushed to metadata" << endl;
//          return db;
//    }
//    else{
//        cerr << "Failed to push schema to metadata" << endl;
//        return db;
//    }
//
//}
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

    // Parse the <Database> element
    XMLElement* dbElement = root->FirstChildElement("Database");
    if (!dbElement) {
        std::cerr << "Invalid XML: No <Database> element found." << std::endl;
        return db;
    }

    const char* dbName = dbElement->Attribute("name");
    if (dbName)
        db.setName(dbName);
    else
        std::cerr << "Database name attribute missing." << std::endl;

    // Map to resolve relation references
    std::map<std::string, Relation*> relationMap;

    // Parse Relations
    XMLElement* relationsElement = dbElement->FirstChildElement("Relations");
    if (relationsElement) {
        for (XMLElement* relationElem = relationsElement->FirstChildElement("Relation");
             relationElem;
             relationElem = relationElem->NextSiblingElement("Relation")) {

            const char* relName = relationElem->Attribute("name");
            if (!relName) {
                std::cerr << "Relation name missing." << std::endl;
                continue;
            }

            Relation* rel = new Relation();
            rel->setName(relName); // Use setName to set the name
            relationMap[relName] = rel;

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
                        CAttribute* attr = new CAttribute(attrName, attrType, isNullable, isUnique);
                        rel->addCAttribute(attr);
                    } else {
                        std::cerr << "Attribute missing name or type in relation " << relName << std::endl;
                    }
                }
            }

            // Parse Primary Key as Constraint
            XMLElement* pkElem = relationElem->FirstChildElement("PrimaryKey");
            if (pkElem) {
                std::vector<std::string> pkAttrs;
                for (XMLElement* attrRef = pkElem->FirstChildElement("AttributeRef");
                     attrRef;
                     attrRef = attrRef->NextSiblingElement("AttributeRef")) {
                    const char* refName = attrRef->Attribute("name");
                    if (refName) {
                        pkAttrs.push_back(refName);
                    }
                }
                if (!pkAttrs.empty()) {
                    PrimaryKeyConstraint* pkCons = new PrimaryKeyConstraint("PK_" + std::string(relName), rel, pkAttrs);
                    db.addConstraint(pkCons);
                    db.addPrimaryKeyConstraint(pkCons);
                }
            }

            db.addRelation(rel);
        }
    }

    // Parse Foreign Keys
    XMLElement* fkElement = dbElement->FirstChildElement("ForeignKeys");
    if (fkElement) {
        for (XMLElement* fkElem = fkElement->FirstChildElement("ForeignKey");
             fkElem;
             fkElem = fkElem->NextSiblingElement("ForeignKey")) {

            const char* fkName = fkElem->Attribute("name");
            if (!fkName) {
                std::cerr << "ForeignKey name missing." << std::endl;
                continue;
            }

            XMLElement* parentElem = fkElem->FirstChildElement("Parent");
            XMLElement* childElem = fkElem->FirstChildElement("Child");
            if (!parentElem || !childElem) {
                std::cerr << "ForeignKey " << fkName << " missing Parent or Child element." << std::endl;
                continue;
            }

            const char* pTableName = parentElem->Attribute("table");
            const char* pColumnName = parentElem->Attribute("column");
            const char* cTableName = childElem->Attribute("table");
            const char* cColumnName = childElem->Attribute("column");

            if (!pTableName || !pColumnName || !cTableName || !cColumnName) {
                std::cerr << "ForeignKey " << fkName << " missing table or column attributes." << std::endl;
                continue;
            }

            auto pTableIt = relationMap.find(pTableName);
            auto cTableIt = relationMap.find(cTableName);
            if (pTableIt == relationMap.end() || cTableIt == relationMap.end()) {
                std::cerr << "ForeignKey " << fkName << " references unknown table." << std::endl;
                continue;
            }

            Relation* pTable = pTableIt->second;
            Relation* cTable = cTableIt->second;

            CAttribute* pColumn = pTable->getCAttribute(pColumnName);
            CAttribute* cColumn = cTable->getCAttribute(cColumnName);
            if (!pColumn || !cColumn) {
                std::cerr << "ForeignKey " << fkName << " references unknown column." << std::endl;
                continue;
            }

            ForeignKeyConstraint* fkCons = new ForeignKeyConstraint(fkName, pTable, pColumn, cTable, cColumn);
            db.addConstraint(fkCons);
            db.addForeignKeyConstraint(fkCons);
        }
    }

    // Parse Unique Constraints
    XMLElement* ucElement = dbElement->FirstChildElement("UniqueConstraints");
    if (ucElement) {
        for (XMLElement* ucElem = ucElement->FirstChildElement("UniqueConstraint");
             ucElem;
             ucElem = ucElem->NextSiblingElement("UniqueConstraint")) {

            const char* ucName = ucElem->Attribute("name");
            const char* relationName = ucElem->Attribute("relation");
            if (!ucName || !relationName) {
                std::cerr << "UniqueConstraint missing name or relation." << std::endl;
                continue;
            }

            auto relIt = relationMap.find(relationName);
            if (relIt == relationMap.end()) {
                std::cerr << "UniqueConstraint " << ucName << " references unknown relation." << std::endl;
                continue;
            }
            Relation* rel = relIt->second;

            std::vector<std::string> attrRefs;
            for (XMLElement* attrRef = ucElem->FirstChildElement("AttributeRef");
                 attrRef;
                 attrRef = attrRef->NextSiblingElement("AttributeRef")) {
                const char* refName = attrRef->Attribute("name");
                if (refName) {
                    attrRefs.push_back(refName);
                }
            }
            if (attrRefs.empty()) {
                std::cerr << "UniqueConstraint " << ucName << " has no attribute references." << std::endl;
                continue;
            }

            UniqueKeyConstraint* ucCons = new UniqueKeyConstraint(ucName, rel, attrRefs);
            db.addConstraint(ucCons);
            db.addUniqueKeyConstraint(ucCons);
        }
    }

    // Parse Views
    XMLElement* viewsElement = dbElement->FirstChildElement("Views");
    if (viewsElement) {
        for (XMLElement* viewElem = viewsElement->FirstChildElement("View");
             viewElem;
             viewElem = viewElem->NextSiblingElement("View")) {

            const char* viewName = viewElem->Attribute("name");
            const char* viewQuery = viewElem->GetText();
            if (!viewName || !viewQuery) {
                std::cerr << "View missing name or query." << std::endl;
                continue;
            }

            View* view = new View();
            view->name = viewName;
            view->query = new Query(viewQuery);
//            view->query->setQuerystring(viewQuery);
            db.addView(view);
        }
    }

//    if (pushSchematoMeta_Metadata(db)) {
//        std::cout << "Schema pushed to metadata" << std::endl;
//    } else {
//        std::cerr << "Failed to push schema to metadata" << std::endl;
//    }

    // Create a copy of the XML file
    std::string dbNameStr = db.getName(); // Assuming getName() exists
    if (!dbNameStr.empty()) {
        fs::path targetDir = "../../Databases/" + dbNameStr;
        fs::path targetPath = targetDir / (dbNameStr + "_schema.xml");

        try {
            // Create directory if it doesn't exist
            fs::create_directories(targetDir);

            // Copy the file
            fs::copy_file(xmlFilePath, targetPath, fs::copy_options::overwrite_existing);
            std::cout << "Schema copied to " << targetPath << std::endl;
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Failed to copy schema file: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Cannot copy schema file: Database name is empty." << std::endl;
    }

    if (db.create()) {
        std::cout << "Database created successfully." << std::endl;
    } else {
        std::cerr << "Failed to create the database." << std::endl;
        // Database Emptydb;
        // return Emptydb;
    }
    return db;
}

//Database* DDLEngine::loadSchema(const std::string& xmlFilePath) {
//    Database* db = new Database(xmlFilePath);
//
//    XMLDocument doc;
//    if (doc.LoadFile(xmlFilePath.c_str()) != XML_SUCCESS) {
//        std::cerr << "Failed to load XML file: " << xmlFilePath << std::endl;
//        return db;
//    }
//
//    // Expected Root Element: <ColumnStoreSchema>
//    XMLElement* root = doc.RootElement();
//    if (!root) {
//        std::cerr << "Invalid XML: No root element." << std::endl;
//        return db;
//    }
//
//    // Parse the <Database> element
//    XMLElement* dbElement = root->FirstChildElement("Database");
//    if (!dbElement) {
//        std::cerr << "Invalid XML: No <Database> element found." << std::endl;
//        return db;
//    }
//
//    const char* dbName = dbElement->Attribute("name");
//    if (dbName)
//        db->setName(dbName);
//    else
//        std::cerr << "Database name attribute missing." << std::endl;
//
//    // Map to resolve relation references
//    std::map<std::string, Relation*> relationMap;
//
//    // Parse Relations
//    XMLElement* relationsElement = dbElement->FirstChildElement("Relations");
//    if (relationsElement) {
//        for (XMLElement* relationElem = relationsElement->FirstChildElement("Relation");
//             relationElem;
//             relationElem = relationElem->NextSiblingElement("Relation")) {
//
//            const char* relName = relationElem->Attribute("name");
//            if (!relName) {
//                std::cerr << "Relation name missing." << std::endl;
//                continue;
//            }
//
//            Relation* rel = new Relation();
//            rel->setName(relName); // Use setName to set the name
//            relationMap[relName] = rel;
//
//            // Parse Attributes
//            XMLElement* attributesElem = relationElem->FirstChildElement("Attributes");
//            if (attributesElem) {
//                for (XMLElement* attrElem = attributesElem->FirstChildElement("Attribute");
//                     attrElem;
//                     attrElem = attrElem->NextSiblingElement("Attribute")) {
//
//                    const char* attrName = attrElem->Attribute("name");
//                    const char* attrType = attrElem->Attribute("type");
//                    bool isNullable = true, isUnique = false;
//                    attrElem->QueryBoolAttribute("isNullable", &isNullable);
//                    attrElem->QueryBoolAttribute("isUnique", &isUnique);
//
//                    if (attrName && attrType) {
//                        CAttribute* attr = new CAttribute(attrName, attrType, isNullable, isUnique);
//                        rel->addCAttribute(attr);
//                    } else {
//                        std::cerr << "Attribute missing name or type in relation " << relName << std::endl;
//                    }
//                }
//            }
//
//            // Parse Primary Key as Constraint
//            XMLElement* pkElem = relationElem->FirstChildElement("PrimaryKey");
//            if (pkElem) {
//                std::vector<std::string> pkAttrs;
//                for (XMLElement* attrRef = pkElem->FirstChildElement("AttributeRef");
//                     attrRef;
//                     attrRef = attrRef->NextSiblingElement("AttributeRef")) {
//                    const char* refName = attrRef->Attribute("name");
//                    if (refName) {
//                        pkAttrs.push_back(refName);
//                    }
//                }
//                if (!pkAttrs.empty()) {
//                    PrimaryKeyConstraint* pkCons = new PrimaryKeyConstraint("PK_" + std::string(relName), rel, pkAttrs);
//                    db->addConstraint(pkCons);
//                }
//            }
//
//            db->addRelation(rel);
//        }
//    }
//
//    // Parse Foreign Keys
//    XMLElement* fkElement = dbElement->FirstChildElement("ForeignKeys");
//    if (fkElement) {
//        for (XMLElement* fkElem = fkElement->FirstChildElement("ForeignKey");
//             fkElem;
//             fkElem = fkElem->NextSiblingElement("ForeignKey")) {
//
//            const char* fkName = fkElem->Attribute("name");
//            if (!fkName) {
//                std::cerr << "ForeignKey name missing." << std::endl;
//                continue;
//            }
//
//            XMLElement* parentElem = fkElem->FirstChildElement("Parent");
//            XMLElement* childElem = fkElem->FirstChildElement("Child");
//            if (!parentElem || !childElem) {
//                std::cerr << "ForeignKey " << fkName << " missing Parent or Child element." << std::endl;
//                continue;
//            }
//
//            const char* pTableName = parentElem->Attribute("table");
//            const char* pColumnName = parentElem->Attribute("column");
//            const char* cTableName = childElem->Attribute("table");
//            const char* cColumnName = childElem->Attribute("column");
//
//            if (!pTableName || !pColumnName || !cTableName || !cColumnName) {
//                std::cerr << "ForeignKey " << fkName << " missing table or column attributes." << std::endl;
//                continue;
//            }
//
//            auto pTableIt = relationMap.find(pTableName);
//            auto cTableIt = relationMap.find(cTableName);
//            if (pTableIt == relationMap.end() || cTableIt == relationMap.end()) {
//                std::cerr << "ForeignKey " << fkName << " references unknown table." << std::endl;
//                continue;
//            }
//
//            Relation* pTable = pTableIt->second;
//            Relation* cTable = cTableIt->second;
//
//            CAttribute* pColumn = pTable->getCAttribute(pColumnName);
//            CAttribute* cColumn = cTable->getCAttribute(cColumnName);
//            if (!pColumn || !cColumn) {
//                std::cerr << "ForeignKey " << fkName << " references unknown column." << std::endl;
//                continue;
//            }
//
//            ForeignKeyConstraint* fkCons = new ForeignKeyConstraint(fkName, pTable, pColumn, cTable, cColumn);
//            db->addConstraint(fkCons);
//        }
//    }
//
//    // Parse Unique Constraints
//    XMLElement* ucElement = dbElement->FirstChildElement("UniqueConstraints");
//    if (ucElement) {
//        for (XMLElement* ucElem = ucElement->FirstChildElement("UniqueConstraint");
//             ucElem;
//             ucElem = ucElem->NextSiblingElement("UniqueConstraint")) {
//
//            const char* ucName = ucElem->Attribute("name");
//            const char* relationName = ucElem->Attribute("relation");
//            if (!ucName || !relationName) {
//                std::cerr << "UniqueConstraint missing name or relation." << std::endl;
//                continue;
//            }
//
//            auto relIt = relationMap.find(relationName);
//            if (relIt == relationMap.end()) {
//                std::cerr << "UniqueConstraint " << ucName << " references unknown relation." << std::endl;
//                continue;
//            }
//            Relation* rel = relIt->second;
//
//            std::vector<std::string> attrRefs;
//            for (XMLElement* attrRef = ucElem->FirstChildElement("AttributeRef");
//                 attrRef;
//                 attrRef = attrRef->NextSiblingElement("AttributeRef")) {
//                const char* refName = attrRef->Attribute("name");
//                if (refName) {
//                    attrRefs.push_back(refName);
//                }
//            }
//            if (attrRefs.empty()) {
//                std::cerr << "UniqueConstraint " << ucName << " has no attribute references." << std::endl;
//                continue;
//            }
//
//            UniqueKeyConstraint* ucCons = new UniqueKeyConstraint(ucName, rel, attrRefs);
//            db->addConstraint(ucCons);
//        }
//    }
//
//    // Parse Views
//    XMLElement* viewsElement = dbElement->FirstChildElement("Views");
//    if (viewsElement) {
//        for (XMLElement* viewElem = viewsElement->FirstChildElement("View");
//             viewElem;
//             viewElem = viewElem->NextSiblingElement("View")) {
//
//            const char* viewName = viewElem->Attribute("name");
//            const char* viewQuery = viewElem->GetText();
//            if (!viewName || !viewQuery) {
//                std::cerr << "View missing name or query." << std::endl;
//                continue;
//            }
//
//            View* view = new View();
//            view->name = viewName;
//            view->query = new Query(viewQuery);
////            view->query->setQuerystring(viewQuery);
//            db->addView(view);
//        }
//    }
//
//    return db;
//}


Database* DDLEngine::loadSchema(const std::string& xmlFilePath) {
    Database* db = new Database();
    db->setName("default"); // Initialize with default name

    XMLDocument doc;
    if (doc.LoadFile(xmlFilePath.c_str()) != XML_SUCCESS) {
        std::cerr << "Failed to load XML file: " << xmlFilePath << std::endl;
        return db;
    }

    XMLElement* root = doc.RootElement();
    if (!root || strcmp(root->Name(), "ColumnStoreSchema") != 0) {
        std::cerr << "Invalid XML: Missing or incorrect root element" << std::endl;
        return db;
    }

    // Parse Database element
    XMLElement* dbElem = root->FirstChildElement("Database");
    if (!dbElem) {
        std::cerr << "Missing Database element" << std::endl;
        return db;
    }

    // Set database name
    const char* dbName = dbElem->Attribute("name");
    if (dbName) db->setName(dbName);

    std::map<std::string, Relation*> relationMap;

    // Parse Relations
    XMLElement* relationsElem = dbElem->FirstChildElement("Relations");
    if (relationsElem) {
        for (XMLElement* relElem = relationsElem->FirstChildElement("Relation");
             relElem; relElem = relElem->NextSiblingElement("Relation")) {

            const char* relName = relElem->Attribute("name");
            if (!relName) continue;

            Relation* rel = new Relation(relName, db);
            relationMap[relName] = rel;

            // Parse Attributes
            XMLElement* attrsElem = relElem->FirstChildElement("Attributes");
            if (attrsElem) {
                for (XMLElement* attrElem = attrsElem->FirstChildElement("Attribute");
                     attrElem; attrElem = attrElem->NextSiblingElement("Attribute")) {

                    const char* attrName = attrElem->Attribute("name");
                    const char* attrType = attrElem->Attribute("type");
                    if (!attrName || !attrType) continue;

                    bool isNullable = attrElem->BoolAttribute("nullable");
                    bool isUnique = attrElem->BoolAttribute("unique");

                    CAttribute* attr = new CAttribute(
                        attrName, attrType, isNullable, isUnique
                    );
                    attr->DatabaseName = db->getName();
                    attr->RelationName = relName;

                    rel->cattributes[attrName] = attr;
                }
            }

            // Parse Primary Key
            XMLElement* pkElem = relElem->FirstChildElement("PrimaryKey");
            if (pkElem) {
                std::vector<std::string> pkAttrs;
                std::vector<CAttribute*> pkAttributes;

                for (XMLElement* attrRef = pkElem->FirstChildElement("AttributeRef");
                     attrRef; attrRef = attrRef->NextSiblingElement("AttributeRef")) {

                    const char* refName = attrRef->Attribute("name");
                    if (!refName) continue;

                    pkAttrs.push_back(refName);
                    if (CAttribute* attr = rel->getCAttribute(refName)) {
                        attr->isPK = true;
                        pkAttributes.push_back(attr);
                    }
                }
                    cout<<"PK Attribute Name "<<pkAttributes[0]->name<<endl;
                if (!pkAttributes.empty()) {
                    PrimaryKey pk("PK_" + std::string(relName), pkAttributes[0], pkAttrs);
                    rel->primaryKey = pk;

                    // Create PrimaryKeyConstraint
                    PrimaryKeyConstraint* pkCons = new PrimaryKeyConstraint(
                        "PKC_" + std::string(relName), rel, pkAttrs, pkAttributes[0]
                    );
                    db->addConstraint(pkCons);
                    db->addPrimaryKeyConstraint(pkCons);
                    rel->pks[pkCons->name] = pkCons;
                }
            }

            db->addRelation(rel);
        }
    }

    // Parse Foreign Keys
    XMLElement* fksElem = dbElem->FirstChildElement("ForeignKeys");
    if (fksElem) {
        for (XMLElement* fkElem = fksElem->FirstChildElement("ForeignKey");
             fkElem; fkElem = fkElem->NextSiblingElement("ForeignKey")) {

            const char* fkName = fkElem->Attribute("name");
            if (!fkName) continue;

            XMLElement* parentElem = fkElem->FirstChildElement("Parent");
            XMLElement* childElem = fkElem->FirstChildElement("Child");
            if (!parentElem || !childElem) continue;

            const char* parentRel = parentElem->Attribute("table");
            const char* parentCol = parentElem->Attribute("column");
            const char* childRel = childElem->Attribute("table");
            const char* childCol = childElem->Attribute("column");

            if (!parentRel || !parentCol || !childRel || !childCol) continue;

            Relation* parent = relationMap[parentRel];
            Relation* child = relationMap[childRel];
            if (!parent || !child) continue;

            CAttribute* parentAttr = parent->getCAttribute(parentCol);
            CAttribute* childAttr = child->getCAttribute(childCol);
            if (!parentAttr || !childAttr) continue;

            // Set FK flags
            childAttr->isFK = true;
            parentAttr->isPK = true; // Assume parent is PK

            // Create ForeignKeyConstraint
            ForeignKeyConstraint* fk = new ForeignKeyConstraint(
                fkName, parent, parentAttr, child, childAttr
            );
            fk->DatabaseName = db->getName();

            db->addConstraint(fk);
            db->addForeignKeyConstraint(fk);
            child->fks[fkName] = fk;
            parent->fks[fkName] = fk;
        }
    }

    // Parse Unique Constraints
    XMLElement* ucsElem = dbElem->FirstChildElement("UniqueConstraints");
    if (ucsElem) {
        for (XMLElement* ucElem = ucsElem->FirstChildElement("UniqueConstraint");
             ucElem; ucElem = ucElem->NextSiblingElement("UniqueConstraint")) {

            const char* ucName = ucElem->Attribute("name");
            const char* relName = ucElem->Attribute("relation");
            if (!ucName || !relName) continue;

            Relation* rel = relationMap[relName];
            if (!rel) continue;

            std::vector<std::string> ucAttrs;
            for (XMLElement* attrRef = ucElem->FirstChildElement("AttributeRef");
                 attrRef; attrRef = attrRef->NextSiblingElement("AttributeRef")) {

                const char* refName = attrRef->Attribute("name");
                if (!refName) continue;

                ucAttrs.push_back(refName);
                if (CAttribute* attr = rel->getCAttribute(refName)) {
                    attr->isUnique = true;
                }
            }

            if (!ucAttrs.empty()) {
                UniqueKeyConstraint* uc = new UniqueKeyConstraint(
                    ucName, rel, ucAttrs, rel->getCAttribute(ucAttrs.at(0))
                );
                db->addConstraint(uc);
                db->addUniqueKeyConstraint(uc);
                rel->uks[ucName] = uc;
            }
        }
    }

    // Parse Views
    XMLElement* viewsElem = dbElem->FirstChildElement("Views");
    if (viewsElem) {
        for (XMLElement* viewElem = viewsElem->FirstChildElement("View");
             viewElem; viewElem = viewElem->NextSiblingElement("View")) {

            const char* viewName = viewElem->Attribute("name");
            const char* query = viewElem->GetText();
            if (!viewName || !query) continue;

            View* view = new View();
            view->name = viewName;
            view->query = new Query(query);
            db->addView(view);
        }
    }

    return db;
}



//using namespace tinyxml2;

//bool DDLEngine::createColumnStoreDBfromXMLSchema(const std::string& xmlFilePath) {
//    // Parse XML file
//    XMLDocument doc;
//    if (doc.LoadFile(xmlFilePath.c_str()) != XML_SUCCESS) {
//        std::cerr << "Failed to load XML file: " << xmlFilePath << std::endl;
//        return false;
//    }
//
//    XMLElement* root = doc.RootElement();
//    XMLElement* databaseElement = root->FirstChildElement("Database");
//    if (!databaseElement) {
//        std::cerr << "Invalid XML: No <Database> element found." << std::endl;
//        return false;
//    }
//
//    std::string dbName = databaseElement->Attribute("name");
//    fs::path dbPath = fs::path("../../Databases") / dbName;
//    fs::create_directories(dbPath);
//
//    // Process relations
//    XMLElement* relationsElement = databaseElement->FirstChildElement("Relations");
//    if (relationsElement) {
//        for (XMLElement* relation = relationsElement->FirstChildElement("Relation"); relation; relation = relation->NextSiblingElement("Relation")) {
//            std::string relationName = relation->Attribute("name");
//            fs::path relationPath = dbPath / relationName;
//            fs::create_directories(relationPath);
//
//            // Process attributes
//            XMLElement* attributesElement = relation->FirstChildElement("Attributes");
//            if (attributesElement) {
//                for (XMLElement* attribute = attributesElement->FirstChildElement("Attribute"); attribute; attribute = attribute->NextSiblingElement("Attribute")) {
//                    std::string attrName = attribute->Attribute("name");
//                    fs::path datFilePath = relationPath / (attrName + ".dat");
//                    std::ofstream datFile(datFilePath);
//                    if (!datFile) {
//                        std::cerr << "Failed to create file: " << datFilePath << std::endl;
//                    }
//                }
//            }
//        }
//    }
//
//    // Process foreign keys
//    XMLElement* foreignKeysElement = databaseElement->FirstChildElement("ForeignKeys");
//    if (foreignKeysElement) {
//        fs::path fkFilePath = dbPath / "foreign_keys.txt";
//        std::ofstream fkFile(fkFilePath);
//        if (!fkFile) {
//            std::cerr << "Failed to create foreign keys file." << std::endl;
//            return false;
//        }
//
//        for (XMLElement* foreignKey = foreignKeysElement->FirstChildElement("ForeignKey"); foreignKey; foreignKey = foreignKey->NextSiblingElement("ForeignKey")) {
//            std::string fkName = foreignKey->Attribute("name");
//            XMLElement* parent = foreignKey->FirstChildElement("Parent");
//            XMLElement* child = foreignKey->FirstChildElement("Child");
//            if (parent && child) {
//                fkFile << "FK: " << fkName << " - "
//                       << "Parent: " << parent->Attribute("table") << "(" << parent->Attribute("column") << ")"
//                       << " -> "
//                       << "Child: " << child->Attribute("table") << "(" << child->Attribute("column") << ")"
//                       << std::endl;
//            }
//        }
//    }
////    dml_engine->databases[dbName] = new Database(xmlFilePath);
//    return true;
//}

//bool DDLEngine::pushSchematoMeta_Metadata(const Database& db){
//    //Now let's push the schema to the meta_metadata file, which is a json file
//    //make sure we're pushing all the dataitems of concerned classes
//    meta_metadata_file << "{\n";
//    meta_metadata_file << "  \"Database\": \"" << db.getName() << "\",\n";
//    meta_metadata_file << "  \"XMLFilePath\": \"" << db.getXmlFilePath() << "\",\n";
//    meta_metadata_file << "  \"Relations\": [\n";
//    for (const auto& relation : db.getRelations()) {
//        meta_metadata_file << "    {\n";
//        meta_metadata_file << "      \"Relation\": \"" << relation.first << "\",\n";
//        meta_metadata_file << "      \"Attributes\": [\n";
//        for (const auto& attr : relation.second->getCAttributes()) {
//            meta_metadata_file << "        {\n";
//            meta_metadata_file << "          \"Attribute\": \"" << attr.first << "\",\n";
//            meta_metadata_file << "          \"Type\": \"" << attr.second->type << "\"\n";
//            meta_metadata_file << "        },\n";
//        }
//        //now, let's store the Primary Key
//        meta_metadata_file << "     Primary Key: " << relation.second->getPrimaryKey().attributeRefs[0] << std::endl;
//
//        meta_metadata_file << "      ]\n";
//        meta_metadata_file << "    },\n";
//    }
//    for (const auto& view : db.getViews()) {
//        meta_metadata_file << "    {\n";
//        meta_metadata_file << "      \"View\": \"" << view.first << "\",\n";
//        meta_metadata_file << "      \"Query\": \"" << view.second->query->getQuerystring() << "\"\n";
//        meta_metadata_file << "    },\n";
//    }
//    for (const auto& constraint : db.getConstraints()) {
//        meta_metadata_file << "    {\n";
//        meta_metadata_file << "      \"Constraint\": \"" << constraint.first << "\",\n";
//        meta_metadata_file << "      \"Type\": \"" << constraint.second->type << "\"\n";
//        meta_metadata_file << "    },\n";
//    }
//
//    meta_metadata_file << "  ]\n";
//    meta_metadata_file << "}\n";
//
//    return true;
//}

// int main(int argc, char* argv[]) {
//     if (argc != 2) {
//         std::cerr << "Usage: " << argv[0] << " <XML file path>" << std::endl;
//         return 1;
//     }
//     createColumnStoreDB(argv[1]);
//     return 0;
// }

