//
// Created by Pradyun Devarakonda on 17/04/25.
//

#ifndef COLVAL_HPP
#define COLVAL_HPP

#include "../include/external_includes.h"
#include "../Schema/Schema_Element.h"
#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"
#include "../Schema/PrimaryKey.h"
#include "../Schema/Constraint.h"
#include "../Schema/View.h"
#include "../ComputationObjects/Query.h"
#include "../Engines/DataLoader.h"
#include "../Engines/DataManipulator.h"
#include "../Engines/DataDeleter.h"
#include "../Engines/QueryManager.h"
#include "../Engines/ViewManager.h"
#include "../Engines/DataStitcher.h"
#include "../CustomTypes/Date_DDMMYYYY_Type.h"

class ColVal {
  public:
  Database* database;
  Relation* relation;
  CAttribute* attribute;
  string strvalue;
  int intvalue;
  double doublevalue;
  Date_DDMMYYYY_Type datevalue;
  bool isNull;
  ColVal();
  ColVal(CAttribute* attribute, const string& strvalue);
  ColVal(CAttribute* attribute, int intvalue);
  ColVal(CAttribute* attribute, double doublevalue);
  ColVal(CAttribute* attribute, Date_DDMMYYYY_Type datevalue);
  ColVal(CAttribute* attribute, bool isNull);
  ColVal(CAttribute* attribute, const string& strvalue, int intvalue, double doublevalue, Date_DDMMYYYY_Type datevalue, bool isNull);
  string getStringValue() const;
  int getIntValue() const;
  double getDoubleValue() const;
  Date_DDMMYYYY_Type getDateValue() const;
  bool isNullValue() const;
  void setStringValue(const string& strvalue);
  void setIntValue(int intvalue);
  void setDoubleValue(double doublevalue);
  void setDateValue(Date_DDMMYYYY_Type datevalue);
  void setNullValue(bool isNull);
  void setValue(const string& strvalue, int intvalue, double doublevalue, Date_DDMMYYYY_Type datevalue, bool isNull);
  void setAttribute(CAttribute* attribute);
  CAttribute* getAttribute() const;
  string getAttributeName() const;
  string getAttributeType() const;
  string getAttributeTypeName() const;
  string getAttributeTypeString() const;
  bool operator==(const ColVal& other) const {
    if (this->isNull != other.isNull) return false;
    if (this->isNull && other.isNull) return true; // both are null

    if (this->attribute->type != other.attribute->type) {
        return false; // type mismatch
    }

    if (this->attribute->type == "INT") {
        return this->intvalue == other.intvalue;
    } else if (this->attribute->type == "FLOAT") {
        return this->doublevalue == other.doublevalue;
    } else if (this->attribute->type == "STRING") {
        return this->strvalue == other.strvalue;
    } else if (this->attribute->type == "DATE") {
        return this->datevalue == other.datevalue;
    }

    return false; // fallback
    }
    std::string getPath() const {
        return "../Databases/" + database->getName() + "/" + relation->getName() + "/" + attribute->getName() + ".dat";
    }
};
//inline bool operator==(const ColVal& a, const ColVal& b) {
//    if (a.isNullValue() || b.isNullValue()) return false;
//    if (a.getAttributeType() != b.getAttributeType()) return false;
//
//    string type = a.getAttributeType();
//    if (type == "int") return a.getIntValue() == b.getIntValue();
//    if (type == "float") return abs(a.getDoubleValue() - b.getDoubleValue()) < 1e-6;
//    if (type == "string") return a.getStringValue() == b.getStringValue();
//    if (type == "Date_DDMMYYYY_Type") return a.getDateValue() == b.getDateValue();
//    return false;
//}

//namespace std {
//    template<>
//    struct hash<ColVal> {
//        std::size_t operator()(const ColVal& cv) const {
//            if (cv.isNullValue()) return 0;
//            std::string type = cv.getAttributeType();
//
//            if (type == "int") return hash<int>()(cv.getIntValue());
//            if (type == "float") return hash<double>()(cv.getDoubleValue());
//            if (type == "string") return hash<std::string>()(cv.getStringValue());
//            if (type == "Date_DDMMYYYY_Type") {
//                auto d = cv.getDateValue();
//                return hash<int>()(d.day * 1000000 + d.month * 10000 + d.year);
//            }
//            return 0;
//        }
//    };
//}
namespace std {
    template<>
    struct hash<ColVal> {
        std::size_t operator()(const ColVal& colVal) const {
            std::size_t seed = 0;
            if (colVal.attribute != nullptr) {
                seed ^= std::hash<std::string>{}(colVal.attribute->getName()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            if (colVal.isNull) {
                seed ^= 0xdeadbeef;
            } else {
                if (colVal.attribute != nullptr) {
                    if (colVal.attribute->type == "INT") {
                        seed ^= std::hash<int>{}(colVal.intvalue) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                    } else if (colVal.attribute->type == "FLOAT") {
                        seed ^= std::hash<double>{}(colVal.doublevalue) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                    } else if (colVal.attribute->type == "STRING") {
                        seed ^= std::hash<std::string>{}(colVal.strvalue) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                    } else if (colVal.attribute->type == "DATE") {
                        seed ^= std::hash<std::string>{}(colVal.datevalue.toString()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                    }
                }
            }
            return seed;
        }
    };
}



#endif //COLVAL_HPP
