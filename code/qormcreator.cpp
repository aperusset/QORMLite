#include "qormcreator.h"
#include "qormdatabase.h"
#include "operations/model/table.h"
#include "operations/model/view.h"

void QORMCreator::createAllAndPopulate(const QORMDatabase &database) const {
    this->createTables(database);
    this->createViews(database);
    this->populate(database);
}

void QORMCreator::createTable(const QORMDatabase &database, const QString &name, const PrimaryKey &primaryKey, const std::list<Field> &fields, const std::list<ForeignKey> &foreignKeys) {
    database.execute(Table(name, primaryKey, fields, foreignKeys));
}

void QORMCreator::createView(const QORMDatabase &database, const QString &name, const Select &select) {
    database.execute(select); // ensure the query is valid
    database.execute(View(name, select));
}

void QORMCreator::insert(const QORMDatabase &database, const Insert &insert) {
    database.execute(insert);
}
