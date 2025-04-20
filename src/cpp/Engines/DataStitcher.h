//
// Created by Pradyun Devarakonda on 12/03/25.
//
#ifndef DATASTITCHER_H
#define DATASTITCHER_H

#include "../include/external_includes.h"
#include "../Schema/Relation.h"
#include <string>
#include <vector>

// DataStitcher is responsible for reading from the column files of a Relation
// and combining (stitching) the data for a given tuple (row) into one buffer.
// In this basic version, we assume that the data for each column can be read
// as a string (for demonstration purposes).
class DataStitcher {
public:
    // Given a Relation, a row index, and the number of columns (or simply all columns),
    // stitch together the tuple's data.
    // Returns a string with concatenated values separated by a delimiter.
    // (In production, you might return a structured tuple or a binary buffer.)
    std::string stitchData(const Relation& relation, int rowIndex);
};

#endif // DATASTITCHER_H


//void * stitchData(Relation r,int offset, int size)