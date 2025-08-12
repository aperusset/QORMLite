#ifndef OPERATIONS_QUERY_SELECTION_COUNT_H_
#define OPERATIONS_QUERY_SELECTION_COUNT_H_

#include <QString>
#include <optional>
#include "operations/query/selection/selection.h"

namespace QORM {

class Count : public Selection {
 public:
    explicit Count(const QString &fieldToCount = Selection::ALL,
                   const std::optional<QString> &renamedTo = std::nullopt,
                   bool distinct = false) :
        Selection([&]() -> QString {
            const auto simplifiedCount = fieldToCount.simplified();
            if (distinct && simplifiedCount == Selection::ALL) {
                throw std::invalid_argument("Cannot count distinctly on " +
                                            Selection::ALL.toStdString());
            }
            return QString("count(") + (distinct ? "distinct " : "") +
                   simplifiedCount + ")";
        }(), renamedTo) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_COUNT_H_
