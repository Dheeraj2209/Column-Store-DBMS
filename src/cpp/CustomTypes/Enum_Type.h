//
// Created by Pradyun Devarakonda on 18/03/25.
//

#ifndef ENUM_TYPE_H
#define ENUM_TYPE_H



class Enum_Type {
    Enum_Type_Supervisor* supervisor;

public:

    Enum_type();
    static Enum_type parse(const std::string& enumStr);
};



#endif //ENUM_TYPE_H
