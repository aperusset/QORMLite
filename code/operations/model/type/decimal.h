#ifndef DECIMAL_H
#define DECIMAL_H

#include <QString>
#include "operations/model/type/type.h"

class Decimal : public Type {
 public:
    static const int DEFAULT_DIGITS = 9;
    static const int DEFAULT_DECIMALS = 2;

    // digits and decimals are just documentation, not constraints
    Decimal(const int digits = DEFAULT_DIGITS,
            const int decimals = DEFAULT_DECIMALS) :
        Type("decimal(" + QString::number(digits) + "," +
             QString::number(decimals) + ")") {}
};

#endif  // DECIMAL_H
