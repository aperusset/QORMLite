#ifndef ASSIGNEMENT_H
#define ASSIGNEMENT_H

#include "operations/operation.h"
#include "bindable.h"
#include <QString>
#include <QVariant>

class Assignement : public Operation, public Bindable {

    const QString fieldName;
    const QString parameter;
    const QVariant value;

public:
    Assignement(QString fieldName, QVariant value);
    auto getFieldName() const -> QString;
    auto getParameter() const -> QString override;
    auto getValue() const -> QVariant override;
    auto generate() const -> QString override;
};


#endif // ASSIGNEMENT_H
