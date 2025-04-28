//
// Created by Pradyun Devarakonda on 11/03/25.
//

#include "CAttribute.h"
// ---------- Attribute Implementation ----------
//CAttribute::CAttribute(const std::string& name, const std::string& type, bool isNullable, bool isUnique, bool isPK)
//    : name(name), type(type), isNullable(isNullable), isUnique(isUnique), isPK(isPK) {if(isPK){isNullable = false; isUnique = true;}
//  		if(type == "int") {
//			this->dataType = INT;
//        }
//        else if(type == "float") {
//            this->dataType = FLOAT;
//        }
//        else if(type == "string") {
//            this->dataType = STRING;
//        }
//        else if(type == "Date_DDMMYYYY_Type") {
//            this->dataType = DATE;
//        }
//    }
//}
//std::string CAttribute::getName() const {
//    return name;
//}
//std::string CAttribute::getType() const {
//    return type;
//}
//bool CAttribute::isNullable() const {
//    return isNullable;
//}
//bool CAttribute::isUnique() const {
//    return isUnique;
//}
//bool CAttribute::isPrimaryKey() const {
//    return isPK;
//}
//std::string CAttribute::getRelationName() const {
//    return RelationName;
//}
//void CAttribute::setRelationName(const std::string& relationName) {
//    RelationName = relationName;
//}