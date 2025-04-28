//
// Created by Pradyun Devarakonda on 17/04/25.
//

#ifndef COLCONTAINER_H
#define COLCONTAINER_H

#include "../include/external_includes.h"
#include "../Schema/Schema_Element.h"
#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"
#include "../Schema/PrimaryKey.h"
#include "../Schema/Constraint.h"
#include "../Schema/View.h"
#include "../ComputationObjects/Query.h"
#include "../Engines/DataLoader.h"
#include "../Engines/DataManipulator.hpp"
#include "../Engines/DataDeleter.h"
#include "../Engines/QueryManager.h"
#include "../Engines/ViewManager.h"
#include "../Engines/DataStitcher.h"
#include "../CustomTypes/Date_DDMMYYYY_Type.h"
#include "ColPage.hpp"

class ColContainer {
    Relation* relation;
    CAttribute* attribute;
    int containerindx;
    vector<ColPage*> colPages;
public:
    ColContainer(Relation* relation, CAttribute* attribute) {
        this->relation = relation;
        this->attribute = attribute;
    }
    Relation* getRelation() const {
        return relation;
    }
    CAttribute* getAttribute() const {
        return attribute;
    }
};



#endif //COLCONTAINER_H
