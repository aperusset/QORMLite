#ifndef OPERATIONS_QUERY_BINDABLE_H_
#define OPERATIONS_QUERY_BINDABLE_H_

#include <QString>
#include <QVariant>

namespace QORM {

class Bindable {
 public:
    virtual auto getParameter() const -> const QString& = 0;
    virtual auto getValue() const -> const QVariant& = 0;
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_BINDABLE_H_
