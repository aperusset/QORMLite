#ifndef DATEFORMATTER_H
#define DATEFORMATTER_H

#include <QString>
#include "operations/query/selection/selection.h"

class DateFormatter : public Selection {
 public:
    DateFormatter(const QString &format, const QString &fieldToFormat,
                  const QString &renameTo) :
        Selection("strftime('" + format + "', " + fieldToFormat + ")",
                  renameTo) {}
};

#endif  // DATEFORMATTER_H
