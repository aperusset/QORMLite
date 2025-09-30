#ifndef OPERATIONS_QUERY_BINDABLE_H_
#define OPERATIONS_QUERY_BINDABLE_H_

#include <QString>
#include <QVariant>

namespace QORM {

class Bindable {
 public:
    virtual auto getName() const -> QString = 0;
    virtual auto getType() const -> QString = 0;
    virtual auto getValue() const -> QVariant = 0;

    auto getParameter() const -> QString;
};

inline auto Bindable::getParameter() const -> QString {
    return this->getName() + this->getType();
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_BINDABLE_H_
