#ifndef OPERATIONS_QUERY_BINDABLE_H_
#define OPERATIONS_QUERY_BINDABLE_H_

#include <QString>
#include <QVariant>

namespace QORM {

class Bindable {
 public:
    virtual auto getParameter() const -> QString = 0;
    virtual auto getValue() const -> QVariant = 0;
    virtual auto isParametrized() const -> bool = 0;
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_BINDABLE_H_
