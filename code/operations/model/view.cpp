#include "view.h"
#include <utility>
#include <string>

View::View(QString viewName, Select select) :
    viewName(std::move(viewName)), select(std::move(select)) {
    if (this->select.hasBindables()) {
        throw std::string("Cannot create a view with parametrized conditions.");
    }
}

auto View::getViewName() const -> QString {
    return this->viewName;
}

auto View::getSelect() const -> Select {
    return this->select;
}

auto View::generate() const -> QString {
    return "create view [" + this->viewName + "] as " + select.generate();
}
