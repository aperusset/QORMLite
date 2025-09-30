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
    auto getFieldName() const -> const QString&;
    auto getName() const -> QString override;
    auto getType() const -> QString override;
    auto getValue() const -> QVariant override;
    auto generate() const -> QString override;
};

inline auto Assignment::getFieldName() const -> const QString& {
    return this->fieldName;
}

inline auto Assignment::getName() const -> QString {
    return this->parameter;
}

inline auto Assignment::getType() const -> QString {
    static const QString type("assignment");
    return type;
}

inline auto Assignment::getValue() const -> QVariant {
    return this->value;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_ASSIGNMENT_H_
