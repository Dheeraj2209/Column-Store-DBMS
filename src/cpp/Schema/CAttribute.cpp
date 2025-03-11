//
// Created by Pradyun Devarakonda on 11/03/25.
//

#include "CAttribute.h"
// ---------- Attribute Implementation ----------
CAttribute::CAttribute(const std::string& name, const std::string& type, bool isNullable, bool isUnique, bool isPK)
    : name(name), type(type), isNullable(isNullable), isUnique(isUnique), isPK(isPK) {if(isPK){isNullable = false; isUnique = true;}}