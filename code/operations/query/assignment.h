#ifndef OPERATIONS_QUERY_ASSIGNMENT_H_
#define OPERATIONS_QUERY_ASSIGNMENT_H_

#include "operations/operation.h"
#include "operations/query/bindable.h"

namespace QORM {

class Assignment : public Operation, public Bindable {
    const QString fieldName;
    const QString parameter;
    const QVariant value;

 public:
    Assignment(QString fieldName, QVariant value);
    auto getFieldName() const -> QString;
    auto getParameter() const -> QString override;
    auto getValue() const -> QVariant override;
    auto isParametrized() const -> bool override;
    auto generate() const -> QString override;
};

inline auto Assignment::getFieldName() const -> QString {
    return this->fieldName;
}

inline auto Assignment::getParameter() const -> QString {
    return this->parameter;
}

inline auto Assignment::getValue() const -> QVariant {
    return this->value;
}

inline auto Assignment::isParametrized() const -> bool {
    return this->value.isValid();
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_ASSIGNMENT_H_
