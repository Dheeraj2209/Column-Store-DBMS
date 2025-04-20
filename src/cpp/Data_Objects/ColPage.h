//
// Created by Pradyun Devarakonda on 17/04/25.
//

#ifndef COLPAGE_H
#define COLPAGE_H

#include "../include/external_includes.h"
#include "../Schema/Schema_Element.h"
#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"
#include "../Schema/PrimaryKey.h"
#include "../Schema/Constraint.h"
#include "../Schema/View.h"
#include "../ComputationObjects/Query.h"
#include "../Engines/DataLoader.h"
#include "../Engines/DataManipulator.h"
#include "../Engines/DataDeleter.h"
#include "../Engines/QueryManager.h"
#include "../Engines/ViewManager.h"
#include "../Engines/DataStitcher.h"
#include "../CustomTypes/Date_DDMMYYYY_Type.h"
#include "ColVal.h"
#define PAGE_MAX_OBJS 4096


class ColPage {
    Relation* relation;
    CAttribute* attribute;
    std::vector<ColVal*> colvals; // Assuming data is stored as strings for simplicity
    unsigned int pageindex; // Index of the page in the container
public:
    ColPage(Relation* relation, CAttribute* attribute);
    Relation* getRelation() const;
    CAttribute* getAttribute() const;
    void addData(const std::string& value);
    void removeData(const std::string& value);
};



#endif //COLPAGE_H
