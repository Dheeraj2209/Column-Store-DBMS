//
// Created by Pradyun Devarakonda on 12/03/25.
//

#ifndef QUERY_H
#define QUERY_H


#include "../include/external_includes.h"
//#include "../Schema/Database.h"
#include "../Schema/Relation.h"
#include "../Schema/Schema_Element.h"
#include "../CustomTypes/Date_DDMMYYYY_Type.h"
//#include  <string>
#include <sstream>
//#include "../Schema/Database.h"
// 🔹 Forward declaration
//class Database;

using namespace std;
class Query {
    std::string querystring;
    //Database sourceDB;
    std::vector<std::string> resultcols;
    std::vector<std::string> conditions;
    std::vector<std::string> participating_relations;
    std::vector<std::string> orderbycols;
public:
    // Constructors
    Query();
    Query(const string& querystring);
    //Query(const string& querystring, Database& sourceDB);

    // Setters
    //void setSourceDB(Database* sourceDB);
    void setQuerystring(const std::string& querystring);
    void setResultcols(const std::vector<std::string>& resultcols);
    void setConditions(const std::vector<std::string>& conditions);
    void setParticipating_relations(const std::vector<std::string>& participating_relations);
    void setOrderbycols(const std::vector<std::string>& orderbycols);

    // Getters
    //Database* getSourceDB() const;
    std::string getQuerystring() const;
    std::vector<std::string> getResultcols() const;
    std::vector<std::string> getConditions() const;
    std::vector<std::string> getParticipating_relations() const;
    std::vector<std::string> getOrderbycols() const;
    
    // Parsers
    void parseQuery();
    std::vector<std::string> split(const std::string& s, char delimiter);
    //void setQuerystring(const string& querystring);
    ~Query();
};



#endif //QUERY_H
