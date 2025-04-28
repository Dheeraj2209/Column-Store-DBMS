//
// Created by Pradyun Devarakonda on 17/04/25.
//

#include "ColVal.hpp"

ColVal::ColVal() {
    attribute = nullptr;
    strvalue = "";
    intvalue = 0;
    doublevalue = 0.0;
    isNull = true;
}
ColVal::ColVal(CAttribute* attribute, const std::string& strvalue) {
    this->attribute = attribute;
    this->strvalue = strvalue;
    this->isNull = false;
    // Convert string to appropriate type based on attribute type
    if (attribute->type == "int") {
        intvalue = std::stoi(strvalue);
    } else if (attribute->type == "double") {
        doublevalue = std::stod(strvalue);
    } else if (attribute->type == "date") {
        datevalue = Date_DDMMYYYY_Type::parse(strvalue);
    }
}

ColVal::ColVal(CAttribute* attribute, int intvalue) {
    this->attribute = attribute;
    this->intvalue = intvalue;
    this->isNull = false;
}
ColVal::ColVal(CAttribute* attribute, double doublevalue) {
    this->attribute = attribute;
    this->doublevalue = doublevalue;
    this->isNull = false;
}
ColVal::ColVal(CAttribute* attribute, Date_DDMMYYYY_Type datevalue) {
    this->attribute = attribute;
    this->datevalue = datevalue;
    this->isNull = false;
}
ColVal::ColVal(CAttribute* attribute, bool isNull) {
    this->attribute = attribute;
    this->isNull = isNull;
}
ColVal::ColVal(CAttribute* attribute, const std::string& strvalue, int intvalue, double doublevalue, Date_DDMMYYYY_Type datevalue, bool isNull) {
    this->attribute = attribute;
    this->strvalue = strvalue;
    this->intvalue = intvalue;
    this->doublevalue = doublevalue;
    this->datevalue = datevalue;
    this->isNull = isNull;
}
std::string ColVal::getStringValue() const {
  if(attribute->type == "string") {
    return strvalue;
    }
    else{
        std::cerr << "Error: Attribute type is not string." << std::endl;
        return "";
    }

}
int ColVal::getIntValue() const {
    if(attribute->type == "int") {
        return intvalue;
    }
    else{
        std::cerr << "Error: Attribute type is not int." << std::endl;
        return 0;
    }
}
double ColVal::getDoubleValue() const {
    if(attribute->type == "double") {
        return doublevalue;
    }
    else{
        std::cerr << "Error: Attribute type is not double." << std::endl;
    }
}
Date_DDMMYYYY_Type ColVal::getDateValue() const {
    if(attribute->type == "date") {
        return datevalue;
    }
    else{
        std::cerr << "Error: Attribute type is not date." << std::endl;
        return Date_DDMMYYYY_Type();
    }
}
bool ColVal::isNullValue() const {
    return isNull;
}

void ColVal::setNullValue(bool isNull) {
    this->isNull = isNull;
}
void ColVal::setValue(const std::string& strvalue) {
  if(attribute->type == "string") {
    this->strvalue = strvalue;
    }
    else{
        std::cerr << "Error: Attribute type is not string." << std::endl;
    }
}
void ColVal::setValue(int intvalue) {
    if(attribute->type == "int") {
        this->intvalue = intvalue;
    }
    else{
        std::cerr << "Error: Attribute type is not int." << std::endl;
    }
}
void ColVal::setValue(double doublevalue) {
    if(attribute->type == "double") {
        this->doublevalue = doublevalue;
    }
    else{
        std::cerr << "Error: Attribute type is not double." << std::endl;
    }
}
void ColVal::setValue(Date_DDMMYYYY_Type datevalue) {
    if(attribute->type == "date") {
        this->datevalue = datevalue;
    }
    else{
        std::cerr << "Error: Attribute type is not date." << std::endl;
    }
}
void ColVal::setAttribute(CAttribute* attribute) {
    this->attribute = attribute;
}
CAttribute* ColVal::getAttribute() const {
    return attribute;
}
std::string ColVal::getAttributeName() const {
    return attribute->name;
}
std::string ColVal::getAttributeType() const {
    return attribute->type;
}
//std::string ColVal::getAttributeTypeName() const {
//    return attribute->type;
//}
//std::string ColVal::getAttributeTypeString() const {
//    return attribute->type;
//}
