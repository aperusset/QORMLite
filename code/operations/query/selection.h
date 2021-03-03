#ifndef SELECTION_H
#define SELECTION_H

#include "operations/operation.h"

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

class Avg : public Selection {
 public:
    Avg(const QString &fieldToAvg, const QString &renameTo);
};

class Count : public Selection {
 public:
    Count(const QString &fieldToCount, const QString &renameTo);
};

class Min : public Selection {
 public:
    Min(const QString &fieldToMin, const QString &renameTo);
};

class Max : public Selection {
 public:
    Max(const QString &fieldToMax, const QString &renameTo);
};

class DateFormatter : public Selection {
 public:
    DateFormatter(const QString &format, const QString &fieldToFormat,
                  const QString &renameTo);
};

class Lower : public Selection {
 public:
    explicit Lower(const QString &fieldToLower);
};

class Upper : public Selection {
 public:
    explicit Upper(const QString &fieldToUpper);
};

#endif  // SELECTION_H
