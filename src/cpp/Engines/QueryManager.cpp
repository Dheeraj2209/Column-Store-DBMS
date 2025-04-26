//
// Created by Pradyun Devarakonda on 12/03/25.
//

#include "QueryManager.h"


QueryManager::QueryManager() { /* Implementation */ }
// Engines/QueryManager.cpp
#include "QueryManager.h"
#include "../Engines/DataStitcher.h"

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

//Relation* QueryManager::executeQuery(const Query& rawQuery) {
//  // 1) Parse the query
//  Query q = rawQuery;
//  q.parseQuery();
//
//  // 2) Must have exactly one table for v0.0
//  auto relNames = q.getParticipating_relations();
//  if (relNames.size() != 1) {
//    cerr << "Only single‑relation queries supported in v0.0\n";
//    return nullptr;
//  }
//  Relation* base = db->getRelation(relNames[0]);
//  if (!base) {
//    cerr << "Relation not found: " << relNames[0] << "\n";
//    return nullptr;
//  }
//
//  // 3) Clone schema (no data)
//  Relation* result = base->createEmptyClone();
//
//  // 4) Copy only the projected columns
//  auto projCols = q.getResultcols();
//  if (projCols.empty()) {
//    // if no projection, default to all columns
//    for (auto& p : base->getCAttributes()) projCols.push_back(p.first);
//  }
//  result->projectColumns(projCols);
//
//  // 5) Scan each row, apply WHERE, then append to result
//  size_t numRows = base->getNumRows();
//  DataStitcher stitcher;
//  for (size_t r = 0; r < numRows; ++r) {
//    if (!rowSatisfiesConditions(base, r, q.getConditions())) continue;
//
//    // Read each projected column’s value
//    for (auto& col : projCols) {
//      // For simplicity we read the stitched string and store it directly
//      string tuple = stitcher.stitchData(*base, (int)r);
//      result->appendValue((int)r, col, tuple.c_str(), tuple.size());
//    }
//  }
//
//  // 6) ORDER BY not implemented in v0.0
//
//  return result;
//}
