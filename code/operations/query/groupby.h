#ifndef GROUPBY_H
#define GROUPBY_H

#include "operations/operation.h"
#include <list>

class GroupBy : public Operation {

    const std::list<QString> fields;

public:
    explicit GroupBy(std::list<QString> fields);
    auto getFields() const -> std::list<QString>;
    auto generate() const -> QString override;
};

#endif // GROUPBY_H
