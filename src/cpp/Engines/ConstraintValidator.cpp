//////
////// Created by Pradyun Devarakonda on 25/04/25.
//////
////
////#include "ConstraintValidator.hpp"
////
////
////static std::unordered_set<ColVal> loadColumnValues(Relation* rel, const std::string& columnName) {
////    std::unordered_set<ColVal> values;
////
////    CAttribute* attr = rel->getCAttributes().at(columnName);
////    std::string type = attr->type;
////    std::string path = "../Databases/" + rel->getDBName() + "/" +
////                       rel->getName() + "/" + columnName + ".dat";
////
////    std::ifstream in(path, std::ios::binary);
////    if (!in) return values;
////
////    if (type == "int") {
////        int64_t val;
////        while (in.read(reinterpret_cast<char*>(&val), sizeof(val))) {
////            values.insert(ColVal(attr, static_cast<int>(val)));
////        }
////    } else if (type == "float") {
////        double f;
////        while (in.read(reinterpret_cast<char*>(&f), sizeof(f))) {
////            values.insert(ColVal(attr, f));
////        }
////    } else if (type == "Date_DDMMYYYY_Type") {
////        Date_DDMMYYYY_Type d;
////        while (in.read(reinterpret_cast<char*>(&d), sizeof(d))) {
////            values.insert(ColVal(attr, d));
////        }
////    } else { // string
////        while (true) {
////            size_t len;
////            if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
////            std::string s(len, '\0');
////            if (!in.read(&s[0], len)) break;
////            values.insert(ColVal(attr, s));
////        }
////    }
////
////    return values;
////}
////
////
////bool ConstraintValidator::validatePrimaryKey(Relation* relation,
////                                             const std::string& columnName,
////                                             const ColVal& value,
////                                             const PrimaryKeyConstraint&)
////{
////    auto values = loadColumnValues(relation, columnName);
////    return values.find(value) == values.end();
////}
////
////bool ConstraintValidator::validateUniqueKey(Relation* relation,
////                                            const std::string& columnName,
////                                            const ColVal& value,
////                                            const UniqueKeyConstraint&)
////{
////    auto values = loadColumnValues(relation, columnName);
////    return values.find(value) == values.end();
////}
////
////bool ConstraintValidator::validateForeignKey(Relation* referencingRelation,
////                                             Relation* referencedRelation,
////                                             const std::string& referencingColumn,
////                                             const std::string& referencedColumn,
////                                             const ColVal& value,
////                                             const ForeignKeyConstraint&)
////{
////    auto values = loadColumnValues(referencedRelation, referencedColumn);
////    return values.find(value) != values.end();
////}
//#include "../Engines/ConstraintValidator.hpp"
//
//bool ConstraintValidator::validatePrimaryKey(Relation* relation, CAttribute* column, const ColVal& value, const PrimaryKeyConstraint* pkConstraint) {
//    std::unordered_set<std::string> existingValues;
//
////    for (const auto& tuple : relation->tuples) {
////        for (const auto& colVal : tuple) {
////            if (colVal.getAttribute() == column && !colVal.isNullValue()) {
////                existingValues.insert(colVal.getStringValue());
////            }
////        }
////    }
//
//    return existingValues.find(value.getStringValue()) == existingValues.end(); // true if not found
//}
//
//bool ConstraintValidator::validateForeignKey(Relation* parentRelation, CAttribute* parentColumn, const ColVal& value, const ForeignKeyConstraint* fkConstraint) {
//    std::unordered_set<std::string> parentValues;
//
////    for (const auto& tuple : parentRelation->tuples) {
////        for (const auto& colVal : tuple) {
////            if (colVal.getAttribute() == parentColumn && !colVal.isNullValue()) {
////                parentValues.insert(colVal.getStringValue());
////            }
////        }
////    }
//
//    return parentValues.find(value.getStringValue()) != parentValues.end(); // true if value exists in parent
//}
//
//bool ConstraintValidator::validateUniqueKey(Relation* relation, CAttribute* column, const ColVal& value, const UniqueKeyConstraint* ukConstraint) {
//    std::unordered_set<std::string> existingValues;
//
////    for (const auto& tuple : relation->tuples) {
////        for (const auto& colVal : tuple) {
////            if (colVal.getAttribute() == column && !colVal.isNullValue()) {
////                existingValues.insert(colVal.getStringValue());
////            }
////        }
////    }
//
//    return existingValues.find(value.getStringValue()) == existingValues.end(); // true if unique
//}
//
// Created by Pradyun Devarakonda on 25/04/25.
//

#include "ConstraintValidator.hpp"
#include "../CustomTypes/Date_DDMMYYYY_Type.h"
#include <fstream>

//------------------------------------------------------------------------------
// Helper: load all values from one column file into an unordered_set<ColVal>
//------------------------------------------------------------------------------
static std::unordered_set<ColVal> loadColumnValues(Relation* rel, CAttribute* attr) {
    std::unordered_set<ColVal> values;
    std::string dbName   = rel->getDBName();
    std::string relName  = rel->getName();
    std::string colName  = attr->getName();
    std::string path     = "../Databases/" + dbName + "/" + relName + "/" + colName + ".dat";

    std::ifstream in(path, std::ios::binary);
    if (!in.is_open()) return values;

    const std::string& type = attr->type;
    if (type == "integer") {
        int64_t v;
        while (in.read(reinterpret_cast<char*>(&v), sizeof(v))) {
            values.insert(ColVal(attr, static_cast<int>(v)));
        }
    }
    else if (type == "decimal") {
        double d;
        while (in.read(reinterpret_cast<char*>(&d), sizeof(d))) {
            values.insert(ColVal(attr, d));
        }
    }
    else if (type == "date") {
        Date_DDMMYYYY_Type dt;
        while (in.read(reinterpret_cast<char*>(&dt), sizeof(dt))) {
            values.insert(ColVal(attr, dt));
        }
    }
    else if (type == "boolean") {
        bool b;
        while (in.read(reinterpret_cast<char*>(&b), sizeof(b))) {
            values.insert(ColVal(attr, b));
        }
    }
    else { // string or fallback
        while (true) {
            size_t len;
            if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
            std::string s(len, '\0');
            if (!in.read(&s[0], len)) break;
            values.insert(ColVal(attr, s));
        }
    }

    in.close();
    return values;
}

//------------------------------------------------------------------------------
// Primary Key: valid if the value is *not* already present
//------------------------------------------------------------------------------
bool ConstraintValidator::validatePrimaryKey(Relation* relation,
                                             const ColVal& value,
                                             const PrimaryKeyConstraint* /*pkConstraint*/)
{
    auto existing = loadColumnValues(relation, value.getAttribute());
    return existing.find(value) == existing.end();
}

//------------------------------------------------------------------------------
// Unique Key: valid if the value is *not* already present
//------------------------------------------------------------------------------
bool ConstraintValidator::validateUniqueKey(Relation* relation,
                                            const ColVal& value,
                                            const UniqueKeyConstraint* /*ukConstraint*/)
{
    auto existing = loadColumnValues(relation, value.getAttribute());
    return existing.find(value) == existing.end();
}

//------------------------------------------------------------------------------
// Foreign Key: valid if the value *does* exist in the parent table/column
//------------------------------------------------------------------------------
bool ConstraintValidator::validateForeignKey(const ForeignKeyConstraint* fkConstraint,
                                             const ColVal& value)
{
    Relation*  parentRel = fkConstraint->parentTable;
    CAttribute* parentCol = fkConstraint->parentColumn;
    auto existing = loadColumnValues(parentRel, parentCol);
    return existing.find(value) != existing.end();
}
