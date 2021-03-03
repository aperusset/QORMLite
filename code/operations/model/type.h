#ifndef TYPE_H
#define TYPE_H

#include "operations/operation.h"

class Type : public Operation {
    const QString name;

 public:
    explicit Type(QString name);
    auto getName() const -> QString;
    auto generate() const -> QString override;
};

class Integer : public Type {
 public:
    Integer();
};

class Decimal : public Type {
 public:
    static const int DEFAULT_DIGITS = 9;
    static const int DEFAULT_DECIMALS = 2;

    // digits and decimals are just documentation, not constraints
    Decimal(const int digits = DEFAULT_DIGITS,
            const int decimals = DEFAULT_DECIMALS);
};

class Varchar : public Type {
 public:
    static const int DEFAULT_SIZE = 255;
    static const QString EMPTY;

    // size is just documentation, not a constraint
    explicit Varchar(const int size = DEFAULT_SIZE);
};

class Date : public Type {
 public:
    static const QString NOW;

    Date();
};

#endif  // TYPE_H
