#include <iostream>
//#include "createDB.h"
#include "Engines/DDLEngine.h"
// int main(int argc, char* argv[]) {
//     if (argc != 2) {//if incorrect number of arguments is provided
//         std::cerr << "Usage: " << argv[0] << " <XML_FILE_PATH>" << std::endl;
//         return 1;
//     }
//     std::string xmlPath = argv[1];

//     // Create Column Store DB
//     bool success = createColumnStoreDB(xmlPath);

//     if (success) {
//         std::cout << "Database created successfully." << std::endl;
//         return 0;
//     } else {
//         std::cout << "Failed to create the database." << std::endl; return 1;
//     }
// }


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <XML_FILE_PATH>" << std::endl;
        return 1;
    }
    
    std::string xmlPath = argv[1];
//    bool created = DDLEngine::createColumnStoreDBfromXMLSchema(xmlPath);
//    if(created){
//        std::cout << "Database created successfully." << std::endl;
//    } else {
//        std::cerr << "Failed to create the database." << std::endl;
//        return 1;
//    }
    Database db = DDLEngine::loadSchemaFromXML(xmlPath);
    
    if (db.getName().empty()) {
        std::cerr << "Error: Database name is empty. XML parsing may have failed." << std::endl;
        return 1;
    }
    
    if (db.create()) {
        std::cout << "Database created successfully." << std::endl;
    } else {
        std::cerr << "Failed to create the database." << std::endl;
        return 1;
    }
    
    return 0;
}
