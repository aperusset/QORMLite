#include "operations/query/insert.h"
#include <utility>

QORM::Insert::Insert(const QString &tableName) : Insert(tableName, {}) {}

QORM::Insert::Insert(const QString &tableName,
                     std::list<Assignment> assignments) :
    TableQuery(tableName), assignments(std::move(assignments)) {
    for (const auto &assignement : this->assignments) {
        this->addBindable(assignement);
    }
}

auto QORM::Insert::generate() const -> QString {
    QString insert = "insert into " + this->getTableName();
    if (this->assignments.empty()) {
        insert += " default values";
    } else {
        QStringList names;
        QStringList values;
        names.reserve(this->assignments.size());
        values.reserve(this->assignments.size());
        for (const auto &assignement : this->assignments) {
            names << assignement.getFieldName();
            values << assignement.getParameter();
        }
        insert += "(" + names.join(",") + ") values (" + values.join(",") + ")";
    }
    return insert.simplified();
}
