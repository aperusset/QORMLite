#include "view.h"

View::View(const QString &viewName, const Select &select) :
    viewName(viewName), select(select) {

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
