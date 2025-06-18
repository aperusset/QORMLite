#ifndef OPERATIONS_QUERY_SELECTION_DATEFORMATTER_H_
#define OPERATIONS_QUERY_SELECTION_DATEFORMATTER_H_

#include <QString>
#include <optional>
#include "operations/query/selection/selection.h"

namespace QORM {

class DateFormatter : public Selection {
 public:
    DateFormatter(const QString &format, const QString &fieldToFormat,
                  const std::optional<QString> &renamedTo = std::nullopt) :
        Selection("strftime('" + format + "', " + fieldToFormat + ")",
                  renamedTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_DATEFORMATTER_H_
