#include "operations/model/view.h"
#include <utility>

QORM::View::View(QString viewName, Select select) :
    viewName(std::move(viewName)), select(std::move(select)) {
    if (this->select.hasBindables()) {
        throw std::invalid_argument(
                    "Cannot create a view with parametrized conditions.");
    }
}

auto QORM::View::generate() const -> QString {
    return "create view if not exists " + this->viewName + " as " +
            select.generate();
}
