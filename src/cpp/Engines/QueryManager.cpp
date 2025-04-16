//
// Created by Pradyun Devarakonda on 12/03/25.
//

#include "QueryManager.h"


QueryManager::QueryManager() { /* Implementation */ }
QueryManager::~QueryManager() { /* Implementation */ }
bool QueryManager::addQuery(const Query& query){return true;}
vector<Relation*> QueryManager::executeQueries(){return vector<Relation*>();//Add correct implementation
   }
Relation * QueryManager::executeQuery(const Query& query){return new Relation();//Add correct implementation
   }