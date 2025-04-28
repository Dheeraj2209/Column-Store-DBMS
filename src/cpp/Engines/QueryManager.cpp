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
    for (ColVal* colVal : row->getColVals()) {
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

Table* QueryManager::executeQuery(const Query& query) {
    // Get the relation name from query
    auto relations = query.getParticipating_relations();
    if (relations.empty()) {
        cerr << "No relation specified in query" << endl;
        return nullptr;
    }

    // Get the relation
    Relation* relation = db->getRelation(relations[0]);
    if (!relation) {
        cerr << "Relation not found: " << relations[0] << endl;
        return nullptr;
    }

    // Create result table
    Table* resultTable = new Table(relation);

    // Get projection columns
    vector<string> projectionCols = query.getResultcols();
    if (projectionCols.empty()) {
        // If no columns specified, select all
        for (const auto& attr : relation->getCAttributes()) {
            projectionCols.push_back(attr.first);
        }
    }

    // Get conditions
    vector<string> conditions = query.getConditions();

    // Use DataStitcher to reconstruct rows
    DataStitcher stitcher;
    int numRows = relation->getNumRows();

    for (int rowIndex = 0; rowIndex < numRows; rowIndex++) {
        // Create a row with all columns first
        Row* row = new Row(relation);

        // Add values for each column
        for (const auto& attr : relation->getCAttributes()) {
            string colValue = stitcher.stitchData(*relation, rowIndex);
            CAttribute* attribute = attr.second;

            ColVal* colVal = new ColVal(attribute);
            if (attribute->type == "int") {
                colVal->setValue(stoi(colValue));
            } else if (attribute->type == "decimal") {
                colVal->setValue(stod(colValue));
            } else if (attribute->type == "date") {
                colVal->setValue(Date_DDMMYYYY_Type::parse(colValue));
            } else {
                colVal->setValue(colValue);
            }

            row->addColVal(colVal);
        }

        // Check if row satisfies all conditions
        bool satisfiesConditions = true;
        for (const string& condition : conditions) {
            if (!evaluateCondition(condition, row)) {
                satisfiesConditions = false;
                break;
            }
        }

        if (satisfiesConditions) {
            // Create projected row with only requested columns
            Row* projectedRow = new Row(relation);
            for (const string& colName : projectionCols) {
                for (ColVal* colVal : row->getColVals()) {
                    if (colVal->getAttributeName() == colName) {
                        projectedRow->addColVal(colVal);
                        break;
                    }
                }
            }
            resultTable->addRow(projectedRow);
        }
    }

    // Handle ORDER BY if specified
    vector<string> orderByCols = query.getOrderbycols();
    if (!orderByCols.empty()) {
        // Sort the rows based on order by columns
        vector<Row*> rows = resultTable->getRows();
        sort(rows.begin(), rows.end(),
            [&orderByCols](const Row* a, const Row* b) {
                for (const string& orderByCol : orderByCols) {
                    for (size_t i = 0; i < a->getColVals().size(); i++) {
                        if (a->getColVals()[i]->getAttributeName() == orderByCol) {
                            string valA = a->getColVals()[i]->getStringValue();
                            string valB = b->getColVals()[i]->getStringValue();
                            if (valA != valB) return valA < valB;
                        }
                    }
                }
                return false;
            });
    }

    return resultTable;
}

