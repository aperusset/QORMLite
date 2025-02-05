#ifndef OPERATIONS_MODEL_TYPE_DECIMAL_H_
#define OPERATIONS_MODEL_TYPE_DECIMAL_H_

#include <QString>
#include "operations/model/type/type.h"

namespace QORM {

class Decimal : public Type {
 public:
    inline static const int DEFAULT_DIGITS = 9;
    inline static const int DEFAULT_DECIMALS = 2;

    // digits and decimals are just documentation, not constraints
    Decimal(const int digits = DEFAULT_DIGITS,
            const int decimals = DEFAULT_DECIMALS) :
        Type("decimal(" + QString::number(digits) + "," +
             QString::number(decimals) + ")") {}
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_TYPE_DECIMAL_H_
