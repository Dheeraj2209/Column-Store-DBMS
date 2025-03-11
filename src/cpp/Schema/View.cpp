//
// Created by Pradyun Devarakonda on 11/03/25.
//

#include "View.h"


// ---------- View Implementation ----------
bool View::create(const fs::path &basePath) const {
    // Create a file for the view definition.
    fs::path viewFile = basePath / (name + "_view.txt");
    std::ofstream outFile(viewFile);
    if (!outFile) {
        std::cerr << "Failed to create view file: " << viewFile << std::endl;
        return false;
    }
    outFile << "View Query: " << query << std::endl;
    return true;
}
View::~View() {}