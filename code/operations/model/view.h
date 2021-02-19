#ifndef VIEW_H
#define VIEW_H

#include "operations/query.h"
#include "operations/query/select.h"

class View : public Query {

    const QString viewName;
    const Select select;

public:
    View(QString viewName, Select select);
    auto getViewName() const -> QString;
    auto getSelect() const -> Select;
    auto generate() const -> QString override;
};

#endif // VIEW_H
