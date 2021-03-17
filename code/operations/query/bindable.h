#ifndef BINDABLE_H
#define BINDABLE_H

#include <QString>
#include <QVariant>

namespace QORM {

class Bindable {
 public:
    virtual auto getParameter() const -> QString = 0;
    virtual auto getValue() const -> QVariant = 0;
};

}  // namespace QORM

#endif  // BINDABLE_H
