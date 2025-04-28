//
// Created by Pradyun Devarakonda on 17/04/25.
//

#include "ColPage.hpp"

ColPage::ColPage(Relation* relation, CAttribute* attribute) {
    this->relation = relation;
    this->attribute = attribute;
}
Relation* ColPage::getRelation() const {
    return relation;
}
CAttribute* ColPage::getAttribute() const {
    return attribute;
}
void ColPage::addData(const std::string& value) {
    if (colvals.size() < PAGE_MAX_OBJS) {
        // Assuming ColVal has a constructor that takes a string
        ColVal* colVal = new ColVal(attribute, value);
        colvals.push_back(colVal);
    } else {
        std::cerr << "Page is full. Cannot add more data." << std::endl;
    }
}
//void ColPage::removeData(const std::string& value) {
//    auto it = std::remove(colvals.begin(), colvals.end(), value);
//    if (it != colvals.end()) {
//        colvals.erase(it, colvals.end());
//    } else {
//        std::cerr << "Value not found in page." << std::endl;
//    }
//}