#ifndef IN_H
#define IN_H

#include <QString>
#include <list>
#include "operations/query/condition/condition.h"
#include "operations/query/select.h"

namespace QORM {

class In : public Condition {
 public:
    explicit In(const QString &field, const Select&);
    explicit In(const QString &field, const std::list<QString>&);
    explicit In(const QString &field, const std::list<int>&);
};

}  // namespace QORM

#endif  // IN_H
