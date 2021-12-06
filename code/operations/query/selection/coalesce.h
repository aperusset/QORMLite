#ifndef OPERATIONS_QUERY_SELECTION_COALESCE_H_
#define OPERATIONS_QUERY_SELECTION_COALESCE_H_

#include <QVariant>
#include <list>
#include "operations/query/selection/selection.h"
#include "operations/query/bindable.h"

namespace QORM {

class Coalesce : public Selection {
 public:
    Coalesce(const QString &field, const QVariant &defaultValue) :
        Coalesce({field}, defaultValue, field) {}
    explicit Coalesce(const std::list<QString> &fields, const QString &renamedTo):
        Coalesce(fields, QVariant(), renamedTo) {}
    Coalesce(const std::list<QString>&, QVariant, const QString&);
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_COALESCE_H_
