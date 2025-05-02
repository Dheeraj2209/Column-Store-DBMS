//
// Created by Pradyun Devarakonda on 12/03/25.
//

// #include "QueryManager.h"



// Engines/QueryManager.cpp
#include "QueryManager.h"
#include "../Engines/DataStitcher.h"
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
    // std::cout << "Executing query: ";
    // std::cout << "\n";
    
    namespace fs = std::filesystem;
    
    // Get the relation name from query
    vector<string> relations = query.getParticipating_relations();
    if (relations.empty()) {
        cerr << "No relation specified in query" << endl;
        return false;
    }

    // 1) Find the relation
    Relation* rel = db->getRelation(relations[0]);
    if (!rel) {
        std::cerr << "Relation " << relations[0] << " not found.\n";
        return false;
    }

    // 2) Gather attributes in schema order
    const auto& attrMap = rel->getCAttributes(); // map<string,CAttribute*>
    std::vector<CAttribute*> attrs;
    attrs.reserve(attrMap.size());
    for (auto const& [name, attr] : attrMap) {
        attrs.push_back(attr);
    }

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
        cols.push_back({ attr, std::move(in) });
    }

    // 4) Print a header row
    for (auto* attr : attrs) {
        std::cout << std::setw(20) << std::left << attr->name;
    }
    std::cout << "\n";
    for (size_t i = 0; i < attrs.size(); ++i) {
        std::cout << std::string(20, '-');
    }
    std::cout << "\n";

    // Get conditions
    vector<string> conditions = query.getConditions();

    // Create a map of column-wise constraints
    std::unordered_map<std::string, std::vector<std::string>> columnWiseConstraints;
    for (const auto& condition : conditions) {
        size_t opPos = condition.find_first_of("=><!");
        if (opPos != std::string::npos) {
            std::string colName = condition.substr(0, opPos);
            colName.erase(remove_if(colName.begin(), colName.end(), ::isspace), colName.end());
            columnWiseConstraints[colName].push_back(condition);
        }
    }

    // 5) Read in lockstep until the first column hits EOF
    while (true) {
        // Attempt to read the deleted-flag from the first column
        uint8_t flag0;
        if (!cols[0].in.read(reinterpret_cast<char*>(&flag0), sizeof(flag0))) {
            // EOF reached
            break;
        }

        // For each column, read its own flag and value
        std::vector<std::string> row;
        // row.reserve(cols.size());
        bool skip = false;
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
            }
            else if (attr->type == "decimal") {
                double d;
                in.read(reinterpret_cast<char*>(&d), sizeof(d));
                cell = std::to_string(d);
            }
            else if (attr->type == "date") {
                Date_DDMMYYYY_Type dt;
                in.read(reinterpret_cast<char*>(&dt), sizeof(dt));
                cell = dt.toString();  // implement this in your Date class
            }
            else { // string
                size_t len;
                in.read(reinterpret_cast<char*>(&len), sizeof(len));
                std::string s(len, '\0');
                in.read(&s[0], len);
                cell = s;
            }

            row.push_back(cell);

            std::string colName = attr->name;

            // Check if there are constraints for this column
            if (columnWiseConstraints.find(colName) != columnWiseConstraints.end()) {
                for (const auto& condition : columnWiseConstraints[colName]) {
                    if (attr->type == "integer") {
                        int64_t intValue = std::stoll(row[i]);
                        if (!evaluateCondition(condition, intValue)) {
                            skip = true;
                            break;
                        }
                    } else if (attr->type == "decimal") {
                        double doubleValue = std::stod(row[i]);
                        if (!evaluateCondition(condition, doubleValue)) {
                            skip = true;
                            break;
                        }
                    } else if (attr->type == "string") {
                        if (!evaluateCondition(condition, row[i])) {
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

            if (skip) break;
        }

        // 6) Skip if deleted
        if (flag0 == 1) {
            continue;
        }

        if (skip) {
            continue;
        }

        // 7) Print the row
        for (auto& cell : row) {
            std::cout << std::setw(20) << std::left << cell;
        }
        std::cout << "\n";
    }

    // 8) Close files
    for (auto& c : cols) {
        c.in.close();
    }

    return true;

    // // Create result table
    // resultTable = new Table(relation);

    // // Get projection columns
    // vector<string> projectionCols = query.getResultcols();
    // if (projectionCols.empty()) {
    //     // If no columns specified, select all
    //     for (const auto& attr : relation->getCAttributes()) {
    //         projectionCols.push_back(attr.first);
    //     }
    // }

    // // Get conditions
    // vector<string> conditions = query.getConditions();

    // // Use DataStitcher to reconstruct rows
    // DataStitcher stitcher;
    // int numRows = relation->getNumRows();

    // for (int rowIndex = 0; rowIndex < numRows; rowIndex++) {
    //     // Create a row with all columns first
    //     Row* row = new Row(relation);

    //     // Add values for each column
    //     for (const auto& attr : relation->getCAttributes()) {
    //         string colValue = stitcher.stitchData(*relation, rowIndex);
    //         CAttribute* attribute = attr.second;

    //         ColVal* colVal = new ColVal(attribute);
    //         if (attribute->type == "int") {
    //             colVal->setValue(static_cast<int64_t>(stoi(colValue)));
    //         } else if (attribute->type == "decimal") {
    //             colVal->setValue(stod(colValue));
    //         } else if (attribute->type == "date") {
    //             colVal->setValue(Date_DDMMYYYY_Type::parse(colValue));
    //         } else {
    //             colVal->setValue(colValue);
    //         }

    //         row->addColVal(colVal);
    //     }

    //     // Check if row satisfies all conditions
    //     bool satisfiesConditions = true;
    //     for (const string& condition : conditions) {
    //         if (!evaluateCondition(condition, row)) {
    //             satisfiesConditions = false;
    //             break;
    //         }
    //     }

    //     if (satisfiesConditions) {
    //         // Create projected row with only requested columns
    //         Row* projectedRow = new Row(relation);
    //         for (const string& colName : projectionCols) {
    //             for (auto &  pcolVal : row->getColVals()) {
    //                 ColVal* colVal = pcolVal.second;
    //                 if (colVal->getAttributeName() == colName) {
    //                     projectedRow->addColVal(colVal);
    //                     break;
    //                 }
    //             }
    //         }
    //         resultTable->addRow(projectedRow);
    //     }
    // }

    // Handle ORDER BY if specified
    // vector<string> orderByCols = query.getOrderbycols();
    // if (!orderByCols.empty()) {
    //     // Sort the rows based on order by columns
    //     vector<Row*> rows = resultTable->getRows();
    //     sort(rows.begin(), rows.end(),
    //         [&orderByCols](const Row* a, const Row* b) {
    //             for (const string& orderByCol : orderByCols) {
    //                 for (size_t i = 0; i < a->getColVals().size(); i++) {
    //                     if (a->getColVals()[i]->getAttributeName() == orderByCol) {
    //                         string valA = a->getColVals()[i]->getStringValue();
    //                         string valB = b->getColVals()[i]->getStringValue();
    //                         if (valA != valB) return valA < valB;
    //                     }
    //                 }
    //             }
    //             return false;
    //         });
    // }

    // return true;
}

