#include "creator.h"
#include "./database.h"
#include "operations/model/table.h"
#include "operations/model/view.h"

void QORM::Creator::createAllAndPopulate(const Database &database) const {
    this->createTables(database);
    this->createViews(database);
    this->populate(database);
}

void QORM::Creator::createTable(const Database &database,
                                const QString &name,
                                const PrimaryKey &primaryKey,
                                const std::list<Field> &fields,
                                const std::list<ForeignKey> &foreignKeys) {
    database.execute(Table(name, primaryKey, fields, foreignKeys));
}

void QORM::Creator::createView(const Database &database,
                               const QString &name, const Select &select) {
    database.execute(select);  // ensure the query is valid
    database.execute(View(name, select));
}

void QORM::Creator::insert(const Database &database, const Insert &insert) {
    database.execute(insert);
}
