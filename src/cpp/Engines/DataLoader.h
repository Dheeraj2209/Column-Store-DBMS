//
// Created by Pradyun Devarakonda on 12/03/25.
//

#ifndef DATALOADER_H
#define DATALOADER_H
#include <fstream>
#include <sstream>
#include "../include/external_includes.h"
#include "../Schema/Database.h"
//#include "../incude/stream_includes.h"
#include "../include/Tbl.hpp"
#include "../Schema/Relation.h"
#include "../Schema/Schema_Element.h"
#include "../CustomTypes/Date_DDMMYYYY_Type.h"
//#include "../include/DMLEngine.h"

using namespace std;
class DataLoader {
public:
    static bool loadDataFromCSV(Database* db, const std::string& CSVfile, const std::string& relationName);
    static bool loadCSVData(Database* db,
                                 const std::string& relationName,
                                 const std::string& csvPath);
};



#endif //DATALOADER_H
