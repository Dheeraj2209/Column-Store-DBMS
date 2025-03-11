//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef CATTRIBUTE_H
#define CATTRIBUTE_H

#include "../include/external_includes.h"

class CAttribute {
public:
    std::string name;
    std::string type;
    bool isNullable;
    bool isUnique;
    bool isPK;
    CAttribute(const std::string& name, const std::string& type, bool isNullable = true, bool isUnique = false, bool isPK=false);
};



#endif //CATTRIBUTE_H
