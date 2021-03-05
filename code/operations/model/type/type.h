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

inline auto Type::getName() const -> QString {
    return this->name;
}

#endif  // TYPE_H
