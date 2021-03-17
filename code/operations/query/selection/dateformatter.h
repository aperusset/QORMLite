#ifndef OPERATIONS_QUERY_SELECTION_DATEFORMATTER_H_
#define OPERATIONS_QUERY_SELECTION_DATEFORMATTER_H_

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class DateFormatter : public Selection {
 public:
    DateFormatter(const QString &format, const QString &fieldToFormat,
                  const QString &renameTo) :
        Selection("strftime('" + format + "', " + fieldToFormat + ")",
                  renameTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_DATEFORMATTER_H_
