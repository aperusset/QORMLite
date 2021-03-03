#ifndef BINDABLE_H
#define BINDABLE_H

#include <QString>
#include <QVariant>

class Bindable {
 public:
    virtual auto getParameter() const -> QString = 0;
    virtual auto getValue() const -> QVariant = 0;
};

#endif  // BINDABLE_H
