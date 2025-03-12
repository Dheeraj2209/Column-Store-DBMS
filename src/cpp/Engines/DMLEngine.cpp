//
// Created by Pradyun Devarakonda on 12/03/25.
//

#include "DMLEngine.h"

bool DMLEngine::loadDatafromCSV(const string & DBname, const string & CSVfile, const string & RelationName){
    return dataLoader.loadCSV(this->databases[DBname], CSVfile, RelationName);
}
bool DMLEngine::insertData(const string & DBname, const string & RelationName, const std::vector<std::string>& values){
    return dataManipulator.insertData(this->databases[DBname], RelationName, values);
}
bool DMLEngine::deleteData(const string & DBname, const string & RelationName, const std::vector<std::string>& values){
    return dataDeleter.deleteData(this->databases[DBname], RelationName, values);
}
bool DMLEngine::updateData(const string & DBname, const string & RelationName, const std::vector<std::string>& values){
    return dataManipulator.updateData(this->databases[DBname], RelationName, values);
}
