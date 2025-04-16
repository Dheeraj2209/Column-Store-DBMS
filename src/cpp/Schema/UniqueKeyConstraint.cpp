//
// Created by Pradyun Devarakonda on 31/03/25.
//

#include "UniqueKeyConstraint.h"

bool UniqueKeyConstraint::create(const fs::path &basePath) const {
    fs::path constraintsFile = basePath / "constraints.txt";
    std::ofstream outFile(constraintsFile, std::ios::app);
    if (!outFile) {
        std::cerr << "Failed to open constraints file: " << constraintsFile << std::endl;
        return false;
    }
    outFile << "UniqueConstraint: " << name << " on Relation: " << relation->getName()
            << " Attributes: ";
    for (const std::string& attr : attributeRefs) {
        outFile << attr << " ";
    }
    outFile << std::endl;
    outFile.close();
    return true;
}