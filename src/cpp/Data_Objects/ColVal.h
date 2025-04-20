//
// Created by Pradyun Devarakonda on 17/04/25.
//

#ifndef COLVAL_H
#define COLVAL_H

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

};



#endif //COLVAL_H
