#include "creator.h"
#include <utility>
#include "./database.h"
#include "operations/model/table.h"
#include "operations/model/view.h"

QORM::Creator::Creator(
        std::list<std::reference_wrapper<const Creator>> requiredCreators) :
        requiredCreators(std::move(requiredCreators)) {
}

void QORM::Creator::addRequiredCreator(const Creator &requiredCreator) {
    this->requiredCreators.emplace_back(std::ref(requiredCreator));
}

auto QORM::Creator::isCreated(const Database &database,
                              const std::list<QString> &existingTables,
                              const std::list<QString> &existingViews)
    const -> bool {
    return database.isConnected() &&
           existingTables.size() == this->tables().size() &&
           existingViews.size() == this->views().size();
}

void QORM::Creator::createAllAndPopulate(const Database &database) const {
    for (const auto &requiredCreator : this->requiredCreators) {
        requiredCreator.get().createAllAndPopulate(database);
    }
    this->createTables(database);
    this->createViews(database);
    this->populate(database);
}

void QORM::Creator::createTable(const Database &database,
                                const QString &name,
                                const PrimaryKey &primaryKey,
                                const std::list<Field> &fields,
                                const std::list<ForeignKey> &foreignKeys,
                                const std::list<Unique> &uniques) {
    database.execute(Table(name, primaryKey, fields, foreignKeys, uniques));
}

void QORM::Creator::createView(const Database &database,
                               const QString &name, const Select &select) {
    database.execute(select);  // ensure the query is valid
    database.execute(View(name, select));
}

void QORM::Creator::insert(const Database &database, const Insert &insert) {
    database.execute(insert);
}
