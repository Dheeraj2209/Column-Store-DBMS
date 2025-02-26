#include <iostream>
#include "createDB.h"

int main() {
    std::string xmlPath = "../xml/sample_instance.xml";
    
    bool success = createColumnStoreDB(xmlPath);
    
    if (success) {
        std::cout << "Database created successfully." << std::endl;
    } else {
        std::cout << "Failed to create the database." << std::endl;
    }

    return 0;
}
