#ifndef SELECTION_H
#define SELECTION_H

#include "operations/operation.h"

namespace QORM {

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

inline auto Selection::getFieldName() const -> QString {
    return this->fieldName;
}

inline auto Selection::getRenamedTo() const -> QString {
    return this->renamedTo;
}

}  // namespace QORM

#endif  // SELECTION_H
