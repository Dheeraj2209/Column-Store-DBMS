//
// Created by Pradyun Devarakonda on 12/03/25.
//

#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "../include/external_includes.h"

#include "../ComputationObjects/Query.h"
#include "../Schema/Relation.h"


class ViewManager {
    std::map<string, Query*> views;

};



#endif //VIEWMANAGER_H
