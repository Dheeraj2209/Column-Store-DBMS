//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef SCHEMA_ELEMENT_H
#define SCHEMA_ELEMENT_H

#include "../include/fsnamespace.h"
#include "../include/external_includes.h"

class Schema_Element {
public:
    std::string name;
    virtual bool create(const fs::path &basePath) const = 0;
    std::string getName() const { return name; }
    virtual ~Schema_Element() {}
};



#endif //SCHEMA_ELEMENT_H
