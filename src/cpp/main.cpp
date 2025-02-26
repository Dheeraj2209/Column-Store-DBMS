#include <iostream>
#include "createDB.h"

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <XML_FILE_PATH>" << std::endl;
        return 1; // Return error code
    }

    std::string xmlPath = argv[1];

    // Create the Column Store DB
    bool success = createColumnStoreDB(xmlPath);

    if (success) {
        std::cout << "Database created successfully." << std::endl;
    } else {
        std::cout << "Failed to create the database." << std::endl;
    }

    return success ? 0 : 1; // Return 0 for success, 1 for failure
}
