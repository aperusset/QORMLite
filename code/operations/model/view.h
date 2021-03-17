#ifndef VIEW_H
#define VIEW_H

#include "operations/query.h"
#include "operations/query/select.h"

namespace QORM {

class View : public Query {
    const QString viewName;
    const Select select;

 public:
    View(QString viewName, Select select);
    auto getViewName() const -> QString;
    auto getSelect() const -> Select;
    auto generate() const -> QString override;
};

inline auto View::getViewName() const -> QString {
    return this->viewName;
}

inline auto View::getSelect() const -> Select {
    return this->select;
}

}  // namespace QORM

#endif  // VIEW_H
