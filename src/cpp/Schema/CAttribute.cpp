//
// Created by Pradyun Devarakonda on 11/03/25.
//

#include "CAttribute.h"
// ---------- Attribute Implementation ----------
CAttribute::CAttribute(const std::string& name, const std::string& type, bool isNullable, bool isUnique)
    : name(name), type(type), isNullable(isNullable), isUnique(isUnique) {}