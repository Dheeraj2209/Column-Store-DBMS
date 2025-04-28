//
// Created by Pradyun Devarakonda on 22/04/25.
//

#ifndef TABLE_HPP
#define TABLE_HPP

#include "../include/external_includes.h"
#include "../Schema/Schema_Element.h"
#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"
#include "Row.hpp"


class Table {
  int totalRowsinRelation;
   vector<Row*> rows;
   Relation* relation;
public:
    Table(Relation* relation) : relation(relation) {}
    Relation* getRelation() const {
        return relation;
    }
    void addRow(Row* row) {
        rows.push_back(row);
    }
    Row* getRow(int index) const {
        if (index < 0 || index >= rows.size()) {
            throw std::out_of_range("Index out of range");
        }
        return rows[index];
    }
    std::vector<Row*> getRows() const {
        return rows;
    }
    void setRow(int index, Row* row) {
        if (index < 0 || index >= rows.size()) {
            throw std::out_of_range("Index out of range");
        }
        rows[index] = row;
    }
    void removeRow(int index) {
        if (index < 0 || index >= rows.size()) {
            throw std::out_of_range("Index out of range");
        }
        rows.erase(rows.begin() + index);
    }
    void clearRows() {
        rows.clear();
    }
    int getSize() const {
        return rows.size();
    }
    std::string toString() const {
        std::string result;
        for (const auto& row : rows) {
            result += row->toString() + "\n";
        }
        return result;
    }
    void printTable() const {
        std::cout << "Table: " << relation->getName() << "\n";
        for (const auto& row : rows) {
            std::cout << row->toString() << "\n";
        }
    }
//    bool findtotalRowsinRelation() {
//        string name = relation->getName(); string pkname = relation->getPrimaryKey().attribute->getName();
//        auto basePath = "../Databases/" + relation->getName() + "/" + relation->getName() + ".dat";
//        std::ifstream file(basePath, std::ios::binary);
//    }
	int getTotalRowsinRelation() const {

        return totalRowsinRelation;
    }

};



#endif //TABLE_HPP
