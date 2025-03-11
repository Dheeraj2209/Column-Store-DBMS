//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef CATTRIBUTE_H
#define CATTRIBUTE_H



class CAttribute {
public:
    std::string name;
    std::string type;
    bool isNullable;
    bool isUnique;

    CAttribute(const std::string& name, const std::string& type, bool isNullable = true, bool isUnique = false);
};



#endif //CATTRIBUTE_H
