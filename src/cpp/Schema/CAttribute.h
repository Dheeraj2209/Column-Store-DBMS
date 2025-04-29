//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef CATTRIBUTE_H
#define CATTRIBUTE_H

#include "../include/external_includes.h"
#include "../include/fsnamespace.h"
#include "../Schema/Schema_Element.h"
//#include "../Schema/PrimaryKey.h"
////#include "../Schema/ForeignKeyConstraint.h"
//#include "../Schema/PrimaryKeyConstraint.h"
//#include "../Schema/UniqueKeyConstraint.h"
//#include "../Schema/Relation.h" // Ensure Relation is fully defined
//#include "Relation.h"
class Database;
class Relation;
enum dataType {INT, FLOAT, STRING, DATE};


class CAttribute  {
public:
    std::string name;
    std::string type;
//    enum dataType {INT, FLOAT, STRING, DATE};
    dataType attributeDataType;
//
    Database* database;
    Relation* relation;
     std::string DatabaseName;
     std::string RelationName;
    dataType getDataType() const {
        return attributeDataType;
    }


    bool isNullable;
    bool isUnique;
    bool isPK;
    bool isFK;
//    CAttribute(const std::string& name, const std::string& type, bool isNullable = true, bool isUnique = false, bool isPK=false, bool isFK=false);
//        : name(name), type(type), isNullable(isNullable), isUnique(isUnique), isPK(isPK), isFK(isFK) {
//        if (type == "int") {
//            this->attributeDataType = INT;
//        } else if (type == "float") {
//            this->attributeDataType = FLOAT;
//        } else if (type == "string") {
//            this->attributeDataType = STRING;
//        } else if (type == "Date_DDMMYYYY_Type") {
//            this->attributeDataType = DATE;
//        }
//    }
    CAttribute(const std::string& name, const std::string& type, bool isNullable = true, bool isUnique = false, bool isPK = false, bool isFK = false)
        : name(name), type(type), isNullable(isNullable), isUnique(isUnique), isPK(isPK), isFK(isFK) {
        if (type == "integer") {
            this->attributeDataType = INT;
        } else if (type == "decimal") {
            this->attributeDataType = FLOAT;
        } else if (type == "string") {
            this->attributeDataType = STRING;
        } else if (type == "date") {
            this->attributeDataType = DATE;
        }
    }
    CAttribute() {}

    std::string getName(){
        return name;
    }
    std::string getType() {
        return type;
    }
    bool getIsNullable() {
        return isNullable;
    }
    bool getIsUnique() {
        return isUnique;
    }

    bool getIsPK() {
        return isPK;
    }

    bool getIsFK() {
        return isFK;
    }
//    bool hasForeignKeyConstraint() const {
//        auto fks = relation->getfks();
//        for (const auto& fk : fks) {
//            if (fk.second->childColumn == this) {
//                return true;
//            }
//        }
//        return false;
//    }
//    ForeignKeyConstraint* getForeignKeyConstraint() const {
//        auto fks = relation->getfks();
//        for (const auto& fk : fks) {
//            if (fk.second->childColumn == this) {
//                return fk.second;
//            }
//        }
//        return nullptr;
//    }
//    PrimaryKeyConstraint* getPrimaryKeyConstraint() const {
//        auto pks = relation->getpks();
//        for (const auto& pk : pks) {
//            if (pk.second->attribute == this) {
//                return pk.second;
//            }
//        }
//        return nullptr;
//    }
//    UniqueKeyConstraint* getUniqueKeyConstraint() const {
//        auto uks = relation->getuks();
//        for (const auto& uk : uks) {
//            if (uk.second->attribute == this) {
//                return uk.second;
//            }
//        }
//        return nullptr;
//    }
    std::string getDatabaseName() const {
        return DatabaseName;
    }
    std::string getRelationName() const {
        return RelationName;
    }
    std::string getAttributeType() const {
        return type;
    }
    std::string getAttributeName() const {
        return name;
    }
    std::string getAttributeTypeName() const {
        return type;
    }

//    Database* getDatabase() const {
//        DMLEngine::Database* database = relation->getDatabase();
//        return database;
//    }
//    Relation* getRelation() const {
//        Database* database = getDatabase();
//        Relation* relation = database->getRelation(RelationName);
//        return relation;
//    }
//    dataType getDataType() const {
//        return dataType;
//    }

};



#endif //CATTRIBUTE_H

