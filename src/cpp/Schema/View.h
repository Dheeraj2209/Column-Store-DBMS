//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef VIEW_H
#define VIEW_H

#include "../include/external_includes.h"
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
