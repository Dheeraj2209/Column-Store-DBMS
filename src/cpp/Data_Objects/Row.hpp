//
// Created by Pradyun Devarakonda on 22/04/25.
//

#ifndef ROW_HPP
#define ROW_HPP

#include "../include/external_includes.h"
#include "../Schema/Schema_Element.h"
#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"
#include "ColVal.hpp"

class Row {
    Relation* relation;
    std::vector<ColVal*> colvals;

public:
    Row(Relation* relation) : relation(relation) {}
    Relation* getRelation() const {
        return relation;
    }
    void addColVal(ColVal* colval) {
        colvals.push_back(colval);
    }
    ColVal* getColVal(int index) const {
        if (index < 0 || index >= colvals.size()) {
            throw std::out_of_range("Index out of range");
        }
        return colvals[index];
    }
    std::vector<ColVal*> getColVals() const {
        return colvals;
    }
    void setColVal(int index, ColVal* colval) {
        if (index < 0 || index >= colvals.size()) {
            throw std::out_of_range("Index out of range");
        }
        colvals[index] = colval;
    }
    void removeColVal(int index) {
        if (index < 0 || index >= colvals.size()) {
            throw std::out_of_range("Index out of range");
        }
        colvals.erase(colvals.begin() + index);
    }
    void clearColVals() {
        colvals.clear();
    }
    int getSize() const {
        return colvals.size();
    }
    std::string toString() const {
        std::string result;
        for (const auto& colval : colvals) {
            result += colval->getStringValue() + " | ";
        }
        return result;
    }
};



#endif //ROW_HPP
