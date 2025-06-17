#ifndef OPERATIONS_QUERY_SELECTION_SELECTION_H_
#define OPERATIONS_QUERY_SELECTION_SELECTION_H_

#include <optional>
#include "operations/operation.h"

namespace QORM {

class Selection : public Operation {
    const QString fieldName;
    const std::optional<QString> renamedTo;

 public:
    explicit Selection(QString fieldName,
                       std::optional<QString> renamedTo = std::nullopt);
    auto getFieldName() const -> const QString&;
    auto getRenamedTo() const -> const QString&;
    auto generate() const -> QString override;
    auto operator == (const Selection&) const -> bool;
    auto operator != (const Selection&) const -> bool;
};

inline auto Selection::getFieldName() const -> const QString& {
    return this->fieldName;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_SELECTION_SELECTION_H_
