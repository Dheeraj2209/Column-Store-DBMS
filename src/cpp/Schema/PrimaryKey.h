//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef PRIMARYKEY_H
#define PRIMARYKEY_H



class PrimaryKey {
public:
    Relation* relation;
    CAttribute* attribute;
    std::vector<std::string> attributeRefs;
};

#endif //PRIMARYKEY_H
