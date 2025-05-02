//
// Created by Pradyun Devarakonda on 12/03/25.
//

// #include "QueryManager.h"



// Engines/QueryManager.cpp
#include "QueryManager.h"
#include "../Engines/DataStitcher.h"

// Global debug control variable
bool DEBUG_MODE = false;
int printwidth = 30;

//QueryManager::QueryManager() { /* Implementation */ }
// Helper: very simple condition evaluator of the form "col = value"
static bool rowSatisfiesConditions(Relation* rel,
                                  size_t rowIdx,
                                  const vector<string>& conditions) {
  DataStitcher stitcher;
  // For simplicity, we assume each condition is exactly "col=value"
  for (auto& cond : conditions) {
    auto pos = cond.find('=');
    if (pos == string::npos) continue;
    string col = cond.substr(0, pos);
    string val = cond.substr(pos+1);
    // read the value of that column at rowIdx
    string actual = stitcher.stitchData(*rel, (int)rowIdx);
    // note: in reality you’d read just that one column, not all stitched data!
    // Here we just do a substring search as a stub:
    if (actual.find(val) == string::npos) return false;
  }
  return true;
}

//Table* executeQuery(const Query& query) {
//
//}

//
// Created by Pradyun Devarakonda on 12/03/25.
//

#include "QueryManager.h"


QueryManager::QueryManager() { /* Implementation */ }
// Engines/QueryManager.cpp
#include "QueryManager.h"
#include "../Engines/DataStitcher.h"

// Helper: evaluates a simple condition like "col = value" or "col > value"
static bool evaluateCondition(const string& condition, const Row* row) {
    // Parse condition into operator and value
    size_t opPos = string::npos;
    string ops[] = {"=", ">", "<", ">=", "<=", "!="};
    string op;

    for (const string& testOp : ops) {
        size_t pos = condition.find(testOp);
        if (pos != string::npos) {
            opPos = pos;
            op = testOp;
            break;
        }
    }

    if (opPos == string::npos) return true; // No condition

    string colName = condition.substr(0, opPos);
    colName.erase(remove_if(colName.begin(), colName.end(), ::isspace), colName.end());

    string value = condition.substr(opPos + op.length());
    value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());

    // Find the column value in the row
    for (auto& pcolVal : row->getColVals()) {
        ColVal* colVal = pcolVal.second;
        if (colVal->getAttributeName() == colName) {
            string rowValue;
            if (colVal->getAttribute()->type == "int") {
                rowValue = to_string(colVal->getIntValue());
            } else if (colVal->getAttribute()->type == "decimal") {
                rowValue = to_string(colVal->getDoubleValue());
            } else if (colVal->getAttribute()->type == "date") {
                rowValue = colVal->getDateValue().toString();
            } else {
                rowValue = colVal->getStringValue();
            }

            // Compare based on operator
            if (op == "=") return rowValue == value;
            if (op == ">") return rowValue > value;
            if (op == "<") return rowValue < value;
            if (op == ">=") return rowValue >= value;
            if (op == "<=") return rowValue <= value;
            if (op == "!=") return rowValue != value;
        }
    }

    return false;
}

// Overloaded evaluateCondition function for integers
static bool evaluateCondition(const std::string& condition, int64_t value) {
    size_t opPos = std::string::npos;
    std::string ops[] = {"=", ">", "<", ">=", "<=", "!="};
    std::string op;

    for (const std::string& testOp : ops) {
        size_t pos = condition.find(testOp);
        if (pos != std::string::npos) {
            opPos = pos;
            op = testOp;
            break;
        }
    }

    if (opPos == std::string::npos) return true; // No condition

    std::string conditionValue = condition.substr(opPos + op.length());
    conditionValue.erase(remove_if(conditionValue.begin(), conditionValue.end(), ::isspace), conditionValue.end());
    
    try {
        int64_t literal = std::stoll(conditionValue);
        if (op == "=") return value == literal;
        if (op == ">") return value > literal;
        if (op == "<") return value < literal;
        if (op == ">=") return value >= literal;
        if (op == "<=") return value <= literal;
        if (op == "!=") return value != literal;
    } catch (const std::invalid_argument&) {
        std::cerr << "Invalid integer literal: " << conditionValue << "\n";
        return false;
    }
    
    return false;
}

// Overloaded evaluateCondition function for doubles
static bool evaluateCondition(const std::string& condition, double value) {
    size_t opPos = std::string::npos;
    std::string ops[] = {"=", ">", "<", ">=", "<=", "!="};
    std::string op;

    for (const std::string& testOp : ops) {
        size_t pos = condition.find(testOp);
        if (pos != std::string::npos) {
            opPos = pos;
            op = testOp;
            break;
        }
    }

    if (opPos == std::string::npos) return true; // No condition

    std::string conditionValue = condition.substr(opPos + op.length());
    conditionValue.erase(remove_if(conditionValue.begin(), conditionValue.end(), ::isspace), conditionValue.end());

    try {
        double literal = std::stod(conditionValue);
        if (op == "=") return value == literal;
        if (op == ">") return value > literal;
        if (op == "<") return value < literal;
        if (op == ">=") return value >= literal;
        if (op == "<=") return value <= literal;
        if (op == "!=") return value != literal;
    } catch (const std::invalid_argument&) {
        std::cerr << "Invalid decimal literal: " << conditionValue << "\n";
        return false;
    }
    
    return false;
}

// Overloaded evaluateCondition function for strings
static bool evaluateCondition(const std::string& condition, const std::string& value) {
    size_t opPos = std::string::npos;
    std::string ops[] = {"=", ">", "<", ">=", "<=", "!="};
    std::string op;

    for (const std::string& testOp : ops) {
        size_t pos = condition.find(testOp);
        if (pos != std::string::npos) {
            opPos = pos;
            op = testOp;
            break;
        }
    }

    if (opPos == std::string::npos) return true; // No condition

    std::string conditionValue = condition.substr(opPos + op.length());
    conditionValue.erase(remove_if(conditionValue.begin(), conditionValue.end(), ::isspace), conditionValue.end());

    // Compare based on operator
    if (op == "=") return value == conditionValue;
    if (op == ">") return value > conditionValue;
    if (op == "<") return value < conditionValue;
    if (op == ">=") return value >= conditionValue;
    if (op == "<=") return value <= conditionValue;
    if (op == "!=") return value != conditionValue;

    return false;
}

bool QueryManager::executeQuery(Database*& db, const Query& query, Table*& resultTable) {
    namespace fs = std::filesystem;

    if (DEBUG_MODE) std::cout << "Executing query: " << query.getQuerystring() << "\n";

    // Get the relation name from query
    std::vector<std::string> relations = query.getParticipating_relations();
    if (relations.empty()) {
        std::cerr << "No relation specified in query" << std::endl;
        return false;
    }
    if (DEBUG_MODE) std::cout << "Relation specified: " << relations[0] << "\n";

    // 1) Find the relation
    Relation* rel = db->getRelation(relations[0]);
    if (!rel) {
        std::cerr << "Relation " << relations[0] << " not found.\n";
        return false;
    }
    if (DEBUG_MODE) std::cout << "Relation found: " << relations[0] << "\n";

    // 2) Gather attributes in schema order
    const auto& attrMap = rel->getCAttributes(); // map<string,CAttribute*>
    std::vector<CAttribute*> attrs;
    attrs.reserve(attrMap.size());
    for (const auto& [name, attr] : attrMap) {
        attrs.push_back(attr);
    }
    if (DEBUG_MODE) std::cout << "Attributes gathered: " << attrs.size() << "\n";

    // 3) Open each column file for binary reading
    std::string base = "../../Databases/" + db->getName() + "/" + relations[0] + "/";
    struct ColIn { CAttribute* attr; std::ifstream in; };
    std::vector<ColIn> cols;
    cols.reserve(attrs.size());

    for (auto* attr : attrs) {
        fs::path p = base + attr->name + ".dat";
        std::ifstream in(p, std::ios::binary);
        if (!in) {
            std::cerr << "Cannot open column file: " << p << "\n";
            return false;
        }
        cols.push_back({attr, std::move(in)});
        if (DEBUG_MODE) std::cout << "Opened column file: " << p << "\n";
    }

    std::vector<std::string> colNames = query.getResultcols();
    // Get the columns to be printed from the query
    std::set<std::string> columnsToPrint(colNames.begin(), colNames.end());
    if (DEBUG_MODE) {
        std::cout << "Columns to print: ";
        for (const auto& col : columnsToPrint) {
            std::cout << col << " ";
        }
        std::cout << "\n";
    }

    // Get conditions
    std::vector<std::string> conditions = query.getConditions();
    if (DEBUG_MODE) std::cout << "Conditions received: " << conditions.size() << "\n";

    // Create a map of column-wise constraints
    std::unordered_map<std::string, std::vector<std::string>> columnWiseConstraints;
    for (const auto& condition : conditions) {
        size_t opPos = condition.find_first_of("=><!");
        if (opPos != std::string::npos) {
            std::string colName = condition.substr(0, opPos);
            colName.erase(remove_if(colName.begin(), colName.end(), ::isspace), colName.end());
            columnWiseConstraints[colName].push_back(condition);
            if (DEBUG_MODE) std::cout << "Mapped condition: " << condition << " to column: " << colName << "\n";
        }
    }
    
    // 4) Print a header row
    for (auto* attr : attrs) {
        if (columnsToPrint.count("*") || columnsToPrint.count(attr->name)) {
            std::cout << std::string(printwidth, '-');
        }
    }
    std::cout << "\n";

    for (auto* attr : attrs) {
        if (columnsToPrint.count("*") || columnsToPrint.count(attr->name)) {
            std::cout << "|" << std::setw(printwidth - 1) << std::left << attr->name;
        }
    }
    std::cout << "|\n";

    for (auto* attr : attrs) {
        if (columnsToPrint.count("*") || columnsToPrint.count(attr->name)) {
            std::cout << std::string(printwidth, '-');
        }
    }
    std::cout << "\n";

    // 5) Read in lockstep until the first column hits EOF
    while (true) {
        // Attempt to read the deleted-flag from the first column
        uint8_t flag0;
        if (!cols[0].in.read(reinterpret_cast<char*>(&flag0), sizeof(flag0))) {
            // EOF reached
            if (DEBUG_MODE) std::cout << "Reached EOF for the first column.\n";
            break;
        }

        // For each column, read its own flag and value
        std::vector<std::string> row;
        bool skip = false;
        if (DEBUG_MODE) std::cout << "Reading a new row...\n";
        for (size_t i = 0; i < cols.size(); ++i) {
            auto& [attr, in] = cols[i];
            uint8_t flag = (i == 0 ? flag0 : 0);
            if (i != 0) {
                // for columns beyond the first, read & discard their flag
                in.read(reinterpret_cast<char*>(&flag), sizeof(flag));
            }

            // now read the actual data
            std::string cell;
            if (attr->type == "integer") {
                int64_t v;
                in.read(reinterpret_cast<char*>(&v), sizeof(v));
                cell = std::to_string(v);
            } else if (attr->type == "decimal") {
                double d;
                in.read(reinterpret_cast<char*>(&d), sizeof(d));
                cell = std::to_string(d);
            } else if (attr->type == "date") {
                Date_DDMMYYYY_Type dt;
                in.read(reinterpret_cast<char*>(&dt), sizeof(dt));
                cell = dt.toString();  // implement this in your Date class
            } else { // string
                size_t len;
                in.read(reinterpret_cast<char*>(&len), sizeof(len));
                std::string s(len, '\0');
                in.read(&s[0], len);
                cell = s;
            }

            row.push_back(cell);
            if (DEBUG_MODE) std::cout << "Read value for column " << attr->name << ": " << cell << "\n";

            std::string colName = attr->name;

            // Check if there are constraints for this column
            if (columnWiseConstraints.find(colName) != columnWiseConstraints.end()) {
                for (const auto& condition : columnWiseConstraints[colName]) {
                    if (DEBUG_MODE) std::cout << "Evaluating condition: " << condition << " for column: " << colName << "\n";
                    if (attr->type == "integer") {
                        int64_t intValue = std::stoll(cell);
                        if (!evaluateCondition(condition, intValue)) {
                            if (DEBUG_MODE) std::cout << "Condition failed for column: " << colName << "\n";
                            skip = true;
                            break;
                        }
                    } else if (attr->type == "decimal") {
                        double doubleValue = std::stod(cell);
                        if (!evaluateCondition(condition, doubleValue)) {
                            if (DEBUG_MODE) std::cout << "Condition failed for column: " << colName << "\n";
                            skip = true;
                            break;
                        }
                    } else if (attr->type == "string") {
                        if (!evaluateCondition(condition, cell)) {
                            if (DEBUG_MODE) std::cout << "Condition failed for column: " << colName << "\n";
                            skip = true;
                            break;
                        }
                    } else {
                        std::cerr << "Unsupported data type for column: " << colName << "\n";
                        skip = true;
                        break;
                    }
                }
            }

            if (skip) {
                if (DEBUG_MODE) std::cout << "Skipping row due to failed condition.\n";
                break;
            }
        }

        // 6) Skip if deleted
        if (flag0 == 1) {
            if (DEBUG_MODE) std::cout << "Skipping row due to deleted flag.\n";
            continue;
        }

        if (skip) {
            continue;
        }

        // 7) Print the row
        if (DEBUG_MODE) std::cout << "Row passed all conditions:\n";
        for (size_t i = 0; i < row.size(); ++i) {
            if (columnsToPrint.count("*") || columnsToPrint.count(attrs[i]->name)) {
                std::cout << "|" << std::setw(printwidth - 1) << std::left << row[i];
            }
        }
        std::cout << "|\n";
    }

    // Print a boundary line below the last row
    for (auto* attr : attrs) {
        if (columnsToPrint.count("*") || columnsToPrint.count(attr->name)) {
            std::cout << std::string(printwidth, '-');
        }
    }
    std::cout << "\n";

    // 8) Close files
    for (auto& c : cols) {
        c.in.close();
        if (DEBUG_MODE) std::cout << "Closed file for column: " << c.attr->name << "\n";
    }

    return true;
}