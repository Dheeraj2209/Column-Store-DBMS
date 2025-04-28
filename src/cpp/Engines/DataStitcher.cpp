//
// Created by Pradyun Devarakonda on 12/03/25.
//

#include "DataStitcher.h"
//
// Created by Pradyun Devarakonda on 12/03/25.
//
#include "DataStitcher.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Helper function: Reads a string record from a column file at a given row index.
// For numeric types, this simplistic version converts them to strings.
// Note: In a more complete system, you would use file offset information.
static std::string readColumnValue(const std::string& filePath, int rowIndex, const std::string& type) {
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open column file: " << filePath << "\n";
        return ""; // Return empty string on error
    }

    // For simplicity, we read line by line.
    // In a real implementation, you would use record offsets.
    std::string line;
    int currentRow = 0;
    while (std::getline(inFile, line)) {
        if (currentRow == rowIndex) {
            inFile.close();
            // For numeric types, you may want to convert binary data to a string.
            // For now, assume that the file is stored as text for demonstration.
            return line;
        }
        currentRow++;
    }
    inFile.close();
    return ""; // Not found
}

std::string DataStitcher::stitchData(const Relation& relation, int rowIndex) {
    std::string dbName = relation.getName();  // Assume Relation provides its parent DB name
    std::string relationName = relation.getName();
    std::vector<std::string> stitchedValues;

    // Assume relation->getCAttributes() returns a map<string, CAttribute*>
    const auto& attrMap = relation.getCAttributes();
    for (const auto& pair : attrMap) {
        const std::string& attrName = pair.first;
        // Construct the expected column file path
        std::string filePath = "../Databases/" + dbName + "/" + relationName + "/" + attrName + ".dat";
        // For demonstration, read value as a string.
        std::string value = readColumnValue(filePath, rowIndex, pair.second->type);
        stitchedValues.push_back(value);
    }

    // For version 0.0, simply join the values with a comma
    std::ostringstream oss;
    for (size_t i = 0; i < stitchedValues.size(); i++) {
        oss << stitchedValues[i];
//        if (i != stitchedValues.size() - 1)
//            oss << \", \";
    }
    return oss.str();
}
