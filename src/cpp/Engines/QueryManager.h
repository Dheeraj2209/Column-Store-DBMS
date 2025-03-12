//
// Created by Pradyun Devarakonda on 12/03/25.
//

#ifndef QUERYMANAGER_H
#define QUERYMANAGER_H

#include "../include/external_includes.h"
#include "../ComputationObjects/Query.h"


class QueryManager {
    vector<Query> queries;
public:
    QueryManager();
    bool addQuery(const Query& query);
    vector<Relation> executeQueries();
    Retation executeQuery(const Query& query);
    ~QueryManager();
};



#endif //QUERYMANAGER_H
