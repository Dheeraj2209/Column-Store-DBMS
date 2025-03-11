//
// Created by Pradyun Devarakonda on 11/03/25.
//

#include "Relation.h"

// ---------- Relation Implementation ----------
bool Relation::create(const fs::path &basePath) const {
    // Create a directory for the relation under the database base path.
    fs::path relationPath = basePath / name;
    try {
        fs::create_directories(relationPath);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error creating relation directory (" << name << "): " << e.what() << std::endl;
        return false;
    }

    // Create a .dat file for each attribute.
    for (const CAttribute &attr : attributes) {
        fs::path filePath = relationPath / (attr.name + ".dat");
        std::ofstream outFile(filePath);
        if (!outFile) {
            std::cerr << "Failed to create attribute file: " << filePath << std::endl;
            return false;
        }
    }
    return true;
}
Relation::~Relation() {}