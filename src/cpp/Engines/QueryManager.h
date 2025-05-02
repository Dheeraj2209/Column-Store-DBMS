//
// Created by Pradyun Devarakonda on 12/03/25.
//

#ifndef QUERYMANAGER_H
#define QUERYMANAGER_H

#include "../include/external_includes.h"
#include "../ComputationObjects/Query.h"
#include "../Schema/Database.h"
#include "../Data_Objects/Table.hpp"
class QueryManager {
    Database* db;
//    vector<Query> queries;
public:
    QueryManager();
    QueryManager(Database* database) : db(database) {}
//    bool addQuery(const Query& query) {
//        queries.push_back(query);
//        return true;
//    }

    // Execute a single query, returning a new Relation* with the result set
    bool executeQuery(Database*& db, const Query& query, Table*& resultTable);

    ~QueryManager() = default;
};



#endif //QUERYMANAGER_H
