#include "insert.h"
#include <utility>

Insert::Insert(const QString &tableName) : Insert(tableName, {}) {}

Insert::Insert(const QString &tableName, std::list<Assignement> assignements) :
    TableQuery(tableName), assignements(std::move(assignements)) {
    for (auto const &assignement : this->assignements) {
        this->addBindable(assignement);
    }
}

auto Insert::getAssignements() const -> std::list<Assignement> {
    return this->assignements;
}

auto Insert::generate() const -> QString {
    QString insert = "insert into " + this->getTableName();
    if (this->assignements.empty()) {
        insert += " default values";
    } else {
        QStringList names;
        QStringList values;
        for (auto const &assignement : this->assignements) {
            names << assignement.getFieldName();
            values << assignement.getParameter();
        }
        insert += "(" + names.join(",") + ") values (" + values.join(",") + ")";
    }
    return insert.simplified();
}
