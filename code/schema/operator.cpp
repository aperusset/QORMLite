#include "operator.h"
#include "./database.h"
#include "operations/model/table.h"
#include "operations/model/view.h"

void QORM::Schema::Operator::setAlreadyExecuted(bool alreadyExecuted) {
    this->alreadyExecuted = alreadyExecuted;
}

void QORM::Schema::Operator::createTable(const Database &database,
        const QString &name, const PrimaryKey &primaryKey,
        const std::list<Field> &fields,
        const std::list<ForeignKey> &foreignKeys,
        const std::list<Unique> &uniques) {
    database.execute(Table(name, primaryKey, fields, foreignKeys, uniques));
}

void QORM::Schema::Operator::createView(const Database &database,
        const QString &name, const Select &select) {
    database.execute(select);  // ensure the query is valid
    database.execute(View(name, select));
}

void QORM::Schema::Operator::insert(const Database &database,
                                    const Insert &insert) {
    database.execute(insert);
}
