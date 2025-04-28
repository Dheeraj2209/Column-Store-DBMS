//
// Created by Pradyun Devarakonda on 18/03/25.
//

#ifndef ENUM_TYPE_H
#define ENUM_TYPE_H

#include "../include/external_includes.h"
#include "Enum_Type_Supervisor.h"

class Enum_Type {
    Enum_Type_Supervisor* supervisor;

public:

    Enum_Type();
    static Enum_Type parse(const std::string& enumStr);
};



#endif //ENUM_TYPE_H
