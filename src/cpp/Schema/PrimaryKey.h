//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef PRIMARYKEY_H
#define PRIMARYKEY_H

#include "../include/external_includes.h"
//#include "../Schema/Relation.h"
//#include "../Schema/CAttribute.h" // Ensure CAttribute is defined
////
//class Relation; // Forward declaration
//class CAttribute; // Forward declaration
#include "CAttribute.h"

class PrimaryKey {
public:
//    Relation* relation;
    std::string DatabaseName;
    std::string relationName;
    CAttribute* attribute;
    std::vector<std::string> attributeRefs;
    std::string name;
    PrimaryKey(const std::string& name, CAttribute* attribute, const std::vector<std::string>& attributeRefs)
        : name(name), attribute(attribute), attributeRefs(attributeRefs) {
        this->relationName = attribute->RelationName;
    }
    PrimaryKey(const std::string& name, CAttribute* attribute)
        : name(name), attribute(attribute) {
        this->relationName = attribute->RelationName;
    }
    PrimaryKey(const std::string& name, CAttribute* attribute, const std::string& relationName)
        : name(name), attribute(attribute), relationName(relationName) {
        this->relationName = relationName;
    }
    PrimaryKey(const std::string& name, CAttribute* attribute, const std::vector<std::string>& attributeRefs, const std::string& relationName)
        : name(name), attribute(attribute), attributeRefs(attributeRefs), relationName(relationName) {
        this->relationName = relationName;
    }
	PrimaryKey() {}
    std::string getName() const {
        return name;
    }
    CAttribute* getAttribute() const {
        return attribute;
    }
    std::vector<std::string> getAttributeRefs() const {
        return attributeRefs;
    }
    std::string getRelationName() const {
        return relationName;
    }
   std::string getDatabaseName() const {
        return DatabaseName;
   }
};


#endif // PRIMARYKEY_H  // ADD MISSING ENDIF