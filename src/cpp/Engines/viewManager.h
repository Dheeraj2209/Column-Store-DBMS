//
// Created by Pradyun Devarakonda on 12/03/25.
//

#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "../include/external_includes.h"

#include "Query.h"
#include "Relation.h"


class viewManager {
    std::map<string, Query> views;

};



#endif //VIEWMANAGER_H
