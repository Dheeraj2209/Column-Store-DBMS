//
// Created by Pradyun Devarakonda on 31/03/25.
//

#include "ForeignKeyConstraint.h"


bool ForeignKeyConstraint::create(const fs::path &basePath) const {
    fs::path constraintsFile = basePath / "constraints.txt";
    std::ofstream outFile(constraintsFile, std::ios::app);
    if (!outFile) {
        std::cerr << "Failed to open constraints file: " << constraintsFile << std::endl;
        return false;
    }
    outFile << "ForeignKey: " << name << " - Parent: " << parentTable->getName()
            << "(" << parentColumn->name << ") -> Child: " << childTable->getName()
            << "(" << childColumn->name << ")" << std::endl;
    outFile.close();
    return true;
}