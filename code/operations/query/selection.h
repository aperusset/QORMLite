#ifndef SELECTION_H
#define SELECTION_H

#include "operations/operation.h"
#include <QString>

class Selection : public Operation {

    const QString fieldName;
    const QString renamedTo;

public:
    explicit Selection(QString fieldName, QString renamedTo = QString());
    auto getFieldName() const -> QString;
    auto getRenamedTo() const -> QString;
    auto generate() const -> QString override;
    auto operator == (const Selection&) const -> bool;
    auto operator != (const Selection&) const -> bool;
};

class Sum : public Selection {

    public:
        Sum(const QString &fieldToSum, const QString &renameTo);
};

class DateFormatter : public Selection {

    public:
        DateFormatter(const QString &format, const QString &fieldToFormat, const QString &renameTo);
};

class Lower : public Selection {

    public:
        explicit Lower(const QString &fieldToLower);
};

#endif // SELECTION_H
