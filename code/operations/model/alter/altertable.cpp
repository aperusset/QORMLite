#include "altertable.h"

QORM::AlterTable::AlterTable(const QString &tableName, Clause clause) :
    TableQuery(tableName), clause(std::move(clause)) {
}

auto QORM::AlterTable::generate() const -> QString {
    return ("alter table " + this->getTableName() + " " +
            this->clause.generate()).simplified();
}
