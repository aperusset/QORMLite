#include "groupby.h"
#include <QStringList>

GroupBy::GroupBy(std::list<QString> fields) :
    fields(std::move(fields)) {

    if (this->fields.empty()) {
        throw std::string("Group by must have at least on field.");
    }
}

auto GroupBy::getFields() const -> std::list<QString> {
    return this->fields;
}

auto GroupBy::generate() const -> QString {
    QStringList fields;
    std::for_each(this->fields.begin(), this->fields.end(), std::back_inserter(fields));
    return "group by " + fields.join(",");
}
