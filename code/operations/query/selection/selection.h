#ifndef OPERATIONS_QUERY_SELECTION_SELECTION_H_
#define OPERATIONS_QUERY_SELECTION_SELECTION_H_

#include "operations/operation.h"
#include "operations/query/bindable.h"

namespace QORM {

class Selection : public Operation, public Bindable {
    const QString fieldName;
    const QString parameter;
    const QVariant value;
    const QString renamedTo;

 public:
    explicit Selection(QString fieldName, QString renamedTo = QString());
    explicit Selection(QVariant value, QString renamedTo = QString());
    auto getFieldName() const -> QString;
    auto getRenamedTo() const -> QString;
    auto getParameter() const -> QString override;
    auto getValue() const -> QVariant override;
    auto generate() const -> QString override;
    auto operator == (const Selection&) const -> bool;
    auto operator != (const Selection&) const -> bool;
};

inline auto Selection::getFieldName() const -> QString {
    return this->fieldName;
}

inline auto Selection::getRenamedTo() const -> QString {
    return this->renamedTo;
}

inline auto Selection::getParameter() const -> QString {
    return this->parameter;
}

inline auto Selection::getValue() const -> QVariant {
    return this->value;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_SELECTION_H_
