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
    string querystring;
    //Database sourceDB;
    vector<std::string> resultcols;
    vector<std::string> conditions;
    vector<std::string> participating_relations;
    vector<std::string> orderbycols;
public:
    // Constructors
    Query();
    Query(const string& querystring);
    //Query(const string& querystring, Database& sourceDB);

    // Setters
    //void setSourceDB(Database* sourceDB);
    void setQuerystring(const string& querystring);
    void setResultcols(const vector<std::string>& resultcols);
    void setConditions(const vector<std::string>& conditions);
    void setParticipating_relations(const vector<std::string>& participating_relations);
    void setOrderbycols(const vector<std::string>& orderbycols);

    // Getters
    //Database* getSourceDB() const;
    string getQuerystring() const;
    vector<std::string> getResultcols() const;
    vector<std::string> getConditions() const;
    vector<std::string> getParticipating_relations() const;
    vector<std::string> getOrderbycols() const;
    
    // Parsers
    void parseQuery();
    vector<std::string> split(const string& s, char delimiter);
    //void setQuerystring(const string& querystring);
    ~Query();
};



#endif //QUERY_H
