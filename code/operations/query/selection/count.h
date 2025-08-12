#ifndef OPERATIONS_QUERY_SELECTION_COUNT_H_
#define OPERATIONS_QUERY_SELECTION_COUNT_H_

#include <QString>
#include <optional>
#include "operations/query/selection/selection.h"

namespace QORM {

class Count : public Selection {
 public:
    explicit Count(const QString &fieldToCount,
                   const std::optional<QString> &renamedTo = std::nullopt,
                   bool distinct = false) :
        Selection(QString("count(") + (distinct ? "distinct " : "") +
                  fieldToCount + ")", renamedTo) {
            if (distinct && fieldToCount.simplified() == Selection::ALL) {
                throw std::invalid_argument("Cannot count distinctly on " +
                                            Selection::ALL.toStdString());
            }
        }
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_COUNT_H_
