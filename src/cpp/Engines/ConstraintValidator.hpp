//
// Created by Pradyun Devarakonda on 25/04/25.
//

#ifndef CONSTRAINTVALIDATOR_HPP
#define CONSTRAINTVALIDATOR_HPP

#include "../Schema/Relation.h"
#include "../Schema/CAttribute.h"
#include "../Schema/PrimaryKeyConstraint.h"
#include "../Schema/UniqueKeyConstraint.h"
#include "../Schema/ForeignKeyConstraint.h"
#include "../Data_Objects/ColVal.hpp"

class ConstraintValidator {
public:
    // Returns true if 'value' does NOT already exist as a PK in that relation/column
    static bool validatePrimaryKey(
        Relation* relation,
        const ColVal& value,
        const PrimaryKeyConstraint* pkConstraint);

    // Returns true if 'value' does NOT already exist as a UK in that relation/column
    static bool validateUniqueKey(
        Relation* relation,
        const ColVal& value,
        const UniqueKeyConstraint* ukConstraint);

    // Returns true if 'value' DOES exist in the parentRelation/parentColumn
    static bool validateForeignKey(
                                             const ColVal& value,
                                             const ForeignKeyConstraint* fkConstraint);
};


#endif // CONSTRAINTVALIDATOR_HPP
