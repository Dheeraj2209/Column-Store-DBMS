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
    // std::vector<ColVal*> colvals;
    std::map<std::string, ColVal*> colvals; // Changed to map for easier access by attribute name
public:
    Row(Relation* relation) : relation(relation) {}

    // New constructor to initialize with Relation* and values
//    Row(const std::vector<std::string>& values, Relation* relation) : relation(relation) {
//        for (const auto& attrPair : relation->getCAttributes()) {
//            CAttribute* attribute = attrPair.second;
//            ColVal* colval = new ColVal(attribute, values[offset++]);
//            colvals.push_back(colval);
//        }
//    }
    // Constructor to initialize with Relation* and values
    // Row(const std::vector<std::string>& values, Relation* relation) : relation(relation) {
    //     int offset = 0;
    //     for (const auto& attrPair : relation->getCAttributes()) {
    //         CAttribute* attribute = attrPair.second;
    //         ColVal* colval = new ColVal(attribute, values[offset++]);
    //         colvals.push_back(colval);
    //     }
    // }
    Row(const std::vector<std::string>& values, Relation* relation) : relation(relation) {
        int offset = 0;
        for (const auto& attrPair : relation->getCAttributes()) {
            CAttribute* attribute = attrPair.second;
            ColVal* colval = new ColVal(attribute, values[offset++]);
            colvals[attrPair.first] = colval; // Store in map
        }
    }
    Row(const std::map<std::string, ColVal*>& colvals, Relation* relation) : colvals(colvals), relation(relation) {}
    Row() : relation(nullptr) {}

    Relation* getRelation() const {
        return relation;
    }
    void addColVal(ColVal* colval) {
        colvals[colval->attribute->getName()] = colval;
    }
    // ColVal* getColVal(int index) const {
    //     if (index < 0 || index >= colvals.size()) {
    //         throw std::out_of_range("Index out of range");
    //     }
    //     return colvals[index];
    // }
    ColVal* getColVal(const std::string& attributeName) const {
        auto it = colvals.find(attributeName);
        if (it != colvals.end()) {
            return it->second;
        }
        return nullptr; // or throw an exception
    }
    // std::vector<ColVal*> getColVals() const {
    //     return colvals;
    // }
    std::map<std::string, ColVal*> getColVals() const {
        return colvals;
    }
    // void setColVal(int index, ColVal* colval) {
    //     if (index < 0 || index >= colvals.size()) {
    //         throw std::out_of_range("Index out of range");
    //     }
    //     colvals[index] = colval;
    // }
    void setColVal(const std::string& attributeName, ColVal* colval) {
        colvals[attributeName] = colval;
    }
    // void removeColVal(int index) {
    //     if (index < 0 || index >= colvals.size()) {
    //         throw std::out_of_range("Index out of range");
    //     }
    //     colvals.erase(colvals.begin() + index);
    // }
    void removeColVal(const std::string& attributeName) {
        colvals.erase(attributeName);
    }
    void clearColVals() {
        colvals.clear();
    }
    int getSize() const {
        return colvals.size();
    }
    // std::string toString() const {
    //     std::string result;
    //     for (const auto& colval : colvals) {
    //         result += colval->getStringValue() + " | ";
    //     }
    //     return result;
    // }
    std::string toString() const {
        std::string result;
        for (const auto& pair : colvals) {
            result += pair.second->getStringValue() + " | ";
        }
        return result;
    }
};



#endif //ROW_HPP
