#ifndef ASSIGNEMENT_H
#define ASSIGNEMENT_H

#include "operations/operation.h"
#include <QString>
#include <QVariant>

class Assignement : public Operation {

    const QString fieldName;
    const QString parameter;
    const QVariant value;

public:
    Assignement(const QString &fieldName, const QVariant &value);
    auto getFieldName() const -> QString;
    auto getParameter() const -> QString;
    auto getValue() const -> QVariant;
    auto generate() const -> QString override;
};


#endif // ASSIGNEMENT_H
