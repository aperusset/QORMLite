#ifndef OPERATIONS_QUERY_BINDABLE_H_
#define OPERATIONS_QUERY_BINDABLE_H_

#include <QString>
#include <QVariant>
#include <utility>
#include "./utils.h"

namespace QORM {

class Bindable {
 public:
    virtual auto getName() const -> QString = 0;
    virtual auto getType() const -> QString = 0;
    virtual auto getValue() const -> const QVariant& = 0;

    auto getParameter() const -> QString;
};

inline auto Bindable::getParameter() const -> QString {
    return this->getName() + this->getType();
}

class Value : public Bindable {
    QString name;
    QVariant value;

 public:
    Value(QString name, QVariant value) :
        name(Utils::parametrize(name)), value(std::move(value)) {}

    auto getName() const -> QString override;
    auto getType() const -> QString override;
    auto getValue() const -> const QVariant& override;
};

inline auto Value::getName() const -> QString {
    return name;
}

inline auto Value::getType() const -> QString {
    return QStringLiteral("value");
}

inline auto Value::getValue() const -> const QVariant& {
    return value;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_BINDABLE_H_
