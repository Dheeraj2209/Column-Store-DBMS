//
// Created by Pradyun Devarakonda on 25/04/25.
//

#ifndef UNIQUEKEY_HPP
#define UNIQUEKEY_HPP

#include "../include/external_includes.h"
#include "../Schema/Schema_Element.h"
#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"


class UniqueKey {
  public:
    Relation* relation;
    CAttribute* attribute;
    std::vector<std::string> attributeRefs;

    UniqueKey(Relation* relation, CAttribute* attribute) {
        this->relation = relation;
        this->attribute = attribute;
    }

};



#endif //UNIQUEKEY_HPP
