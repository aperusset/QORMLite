#include "drop.h"
#include <utility>

QORM::Drop::Drop(DropType dropType, QString name) :
        dropType(dropType), name(std::move(name)) {
    if (this->name.simplified().isEmpty()) {
        throw std::invalid_argument("Drop name must not be blank");
    }
}

auto QORM::Drop::generate() const -> QString {
    QString query("drop ");
    switch (this->dropType) {
        case DropType::Table:
            query += "table";
            break;
        case DropType::View:
            query += "view";
            break;
        case DropType::Trigger:
            query += "trigger";
            break;
        default:
            throw std::logic_error("Unknown drop type");
    }
    return (query += " if exists " + this->name).simplified();
}
