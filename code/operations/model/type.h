#ifndef TYPE_H
#define TYPE_H

#include "operations/operation.h"

class Type : public Operation {

    const QString name;

public:
    explicit Type(const QString &name);
    auto getName() const -> QString;
    auto generate() const -> QString override;
};

class Integer : public Type {

public:
   Integer();
};

class Decimal : public Type {

    // number of digits/decimals is just documentation, not constraints
    const int digits;
    const int decimals;

public:
    Decimal(const int digits = 9, const int decimals = 2);
    auto getDigits() const -> int;
    auto getDecimals() const -> int;
    auto generate() const -> QString override;
};

class Varchar : public Type {

    // size is just documentation, not a constraint
    const int size;

public:
    explicit Varchar(const int size = 255);
    auto getSize() const -> int;
    auto generate() const -> QString override;
};

class Date : public Type {

public:
   Date();
};

namespace QORMType {

    const Integer integer;
    const Decimal decimal;
    const Varchar varchar;
    const Date date;
}

#endif // TYPE_H
