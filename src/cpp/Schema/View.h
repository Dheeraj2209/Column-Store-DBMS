//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef VIEW_H
#define VIEW_H

#include "../include/external_includes.h"

#if __cplusplus >= 201703L // Check if C++17 or later is supported
#include <filesystem> // Include the filesystem header
namespace fs = std::filesystem; // Add a namespace alias for std::filesystem
#else
#error "C++17 or later is required for std::filesystem"
#endif

//#include "../include/fsnamespace.h"
#include "Schema_Element.h"
#include "../ComputationObjects/Query.h"

// View : Named Query
class View : public Schema_Element {
public:
      string name;
      Query* query;  // view definition (e.g. an SQL query)

    // The create() method writes the view definition into a file.
    virtual bool create(const fs::path &basePath) const override;
    ~View();
};



#endif //VIEW_H

