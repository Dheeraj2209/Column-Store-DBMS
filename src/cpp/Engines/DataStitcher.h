//
// Created by Pradyun Devarakonda on 12/03/25.
//

#ifndef DATASTITCHER_H
#define DATASTITCHER_H

#include "../include/external_includes.h"
#include "../Schema/Relation.h"

class DataStitcher {
    void * stitchData(Relation r,int offset, int size);//stitch data belonging to a tuple from different column files
};



#endif //DATASTITCHER_H
