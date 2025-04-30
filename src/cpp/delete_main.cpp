#include <iostream>
#include "Engines/DMLEngine.h"
#include "Data_Objects/ColVal.hpp"
#include "Schema/CAttribute.h"

int main() {
    DMLEngine engine;
//    engine.init();
    auto dbName = "ECommerceDB_main";
//    auto relName = "Customer";
//    auto pkAttrName = "CustomerID";
   Database* db = engine.getDatabase(dbName);
    // load schema (assumes you’ve already run create)
//    engine.createColumnStoreDBfromXMLSchema("ECommerceDB");

    // specify primary-key attribute & value
    // e.g. delete CustomerID=2 from Customer
//    CAttribute pkAttr("CustomerID","integer",false,false,true);
//    ColVal pkVal(&pkAttr, 2);
//    pkattr = db->getRelation("Customer")->getPrimaryKey().attribute;
   int val = 8;
    if (!engine.row_delete(dbName,"Customer", val)) {
        std::cerr<<"Deletion failed\n";
        return 1;
    }
    std::cout<<"Deletion succeeded.\n";
    return 0;
}
