//
// Created by Pradyun Devarakonda on 14/03/25.
//

#ifndef DATE_DDMMYYYY_TYPE_H
#define DATE_DDMMYYYY_TYPE_H

#include "../include/external_includes.h"

class Date_DDMMYYYY_Type {
public:
    uint16_t day;
    uint16_t month;
    uint16_t year;

    Date_DDMMYYYY_Type();
    static std::string dateToString(const Date_DDMMYYYY_Type& date);
    static Date_DDMMYYYY_Type parse(const std::string& dateStr);
    bool operator==(const Date_DDMMYYYY_Type& other) const {
        return (day == other.day && month == other.month && year == other.year);
    }
    std::string toString() const {
        return dateToString(*this);
    }
};




#endif //DATE_DDMMYYYY_TYPE_H
