//
// Created by Pradyun Devarakonda on 14/03/25.
//

#include "Date_DDMMYYYY_Type.h"


Date_DDMMYYYY_Type::Date_DDMMYYYY_Type() : day(0), month(0), year(0) {}
static Date_DDMMYYYY_Type parse(const std::string& dateStr) {
    Date_DDMMYYYY_Type date;
    if (sscanf(dateStr.c_str(), "%2hu/%2hu/%4hu", &date.day, &date.month, &date.year) != 3) {
        throw std::invalid_argument("Invalid date format. Expected DD/MM/YYYY.");
    }
    return date;
}