//
// Created by Pradyun Devarakonda on 25/04/25.
//

#ifndef FOREIGNKEY_HPP
#define FOREIGNKEY_HPP

#include "../include/external_includes.h"
#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"



class ForeignKey {
public:
    CAttribute* parentColumn;
    CAttribute* childColumn;
    Relation* parentTable;
    Relation* childTable;

    ForeignKey(CAttribute* parentColumn, CAttribute* childColumn, Relation* parentTable, Relation* childTable) {
        this->parentColumn = parentColumn;
        this->childColumn = childColumn;
        this->parentTable = parentTable;
        this->childTable = childTable;
    }
};



#endif //FOREIGNKEY_HPP
