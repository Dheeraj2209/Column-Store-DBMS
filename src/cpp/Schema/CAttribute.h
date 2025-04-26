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
    enum dataType {INT, FLOAT, STRING, DATE};
    bool isNullable;
    bool isUnique;
    bool isPK;
    CAttribute(const std::string& name, const std::string& type, bool isNullable = true, bool isUnique = false, bool isPK=false);
    std::string getName() const;
    std::string getType() const;
    bool getIsNullable() const;
    bool getIsUnique() const;
    bool getIsPK() const;
    dataType getDataType() const {
        return dataType;
    }

};



#endif //CATTRIBUTE_H
