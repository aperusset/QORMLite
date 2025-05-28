#ifndef OPERATIONS_MODEL_VIEW_H_
#define OPERATIONS_MODEL_VIEW_H_

#include "operations/query.h"
#include "operations/query/select.h"

namespace QORM {

class View : public Query {
    const QString viewName;
    const Select select;

 public:
    View(QString viewName, Select select);
    inline auto getViewName() const -> const QString&;
    inline auto getSelect() const -> const Select&;
    auto generate() const -> QString override;
};

auto View::getViewName() const -> const QString& {
    return this->viewName;
}

auto View::getSelect() const -> const Select& {
    return this->select;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_VIEW_H_
