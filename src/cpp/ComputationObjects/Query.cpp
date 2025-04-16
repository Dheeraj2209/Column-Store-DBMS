//
// Created by Pradyun Devarakonda on 12/03/25.
//

#include "Query.h"
//#include "../Schema/Database.h"

Query::Query(const string& querystring) : querystring(querystring) {
    // Parse the query string
    parseQuery();
}

//Query::Query(const string& querystring, Database& sourceDB) : querystring(querystring), sourceDB(sourceDB) {
//    // Parse the query string
//    parseQuery();
//}
//
//void Query::setSourceDB(Database& sourceDB) {
//    this->sourceDB = sourceDB;
//}

void Query::setQuerystring(const string& querystring) {
    this->querystring = querystring;
    parseQuery();
}

void Query::setResultcols(const vector<std::string>& resultcols) {
    this->resultcols = resultcols;
}

void Query::setConditions(const vector<std::string>& conditions) {
    this->conditions = conditions;
}

void Query::setParticipating_relations(const vector<std::string>& participating_relations) {
    this->participating_relations = participating_relations;
}

void Query::setOrderbycols(const vector<std::string>& orderbycols) {
    this->orderbycols = orderbycols;
}

//Database Query::getSourceDB() const {
//    return sourceDB;
//}
//
string Query::getQuerystring() const {
    return querystring;
}

vector<std::string> Query::getResultcols() const {
    return resultcols;
}

vector<std::string> Query::getConditions() const {
    return conditions;
}

vector<std::string> Query::getParticipating_relations() const {
    return participating_relations;
}

vector<std::string> Query::getOrderbycols() const {
    return orderbycols;
}

Query::~Query() {}

void Query::parseQuery() {
    stringstream ss(querystring);
    string token;

    std::transform(querystring.begin(), querystring.end(), querystring.begin(), ::tolower);

    // Extract SELECT
    if (querystring.find("select") != 0) {
        throw runtime_error("Invalid query format. Must start with SELECT.");
    }
    ss.ignore(7, ' '); // Skip "SELECT "

    // Extract result columns
    getline(ss, token, ' ');
    size_t fromPos = token.find("from");
    if (fromPos != string::npos) {
        resultcols = split(token.substr(0, fromPos), ',');
        token = token.substr(fromPos + 4); // Move past "from"
    } else {
        resultcols = split(token, ',');
        ss >> token; // Read "from"
    }

    // Extract table name(s)
    getline(ss, token, ' ');
    size_t wherePos = token.find("where");
    if (wherePos != string::npos) {
        participating_relations = split(token.substr(0, wherePos), ',');
        token = token.substr(wherePos + 5); // Move past "where"
    } else {
        participating_relations = split(token, ',');
        ss >> token; // Read "where"
    }

    // Extract conditions if present
    if (!ss.eof()) {
        getline(ss, token, ' ');
        if (token.find("order by") != string::npos) {
            orderbycols = split(token.substr(8), ',');
        } else {
            conditions = split(token, ',');
            if (!ss.eof()) {
                ss >> token; // Read "order by"
                if (token == "order") {
                    ss >> token; // Read "by"
                    getline(ss, token);
                    orderbycols = split(token, ',');
                }
            }
        }
    }
}

vector<std::string> Query::split(const string& str, char delimiter) {
    vector<std::string> tokens;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delimiter)) {
        item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
        tokens.push_back(item);
    }
    return tokens;
}

//void Query::setQuerystring(const string& querystring) {
//    this->querystring = querystring;
//    parseQuery();
//}
//Query::~Query() {}
