#include "creator.h"
#include <utility>
#include "./database.h"
#include "operations/model/table.h"
#include "operations/model/view.h"

QORM::Schema::Creator::Creator(CreatorList requiredCreators,
                               UpgraderList upgraders) :
        requiredCreators(std::move(requiredCreators)),
        upgraders(std::move(upgraders)) {
    this->sortUpgraders();
}

void QORM::Schema::Creator::sortUpgraders() {
    this->upgraders.sort([](const auto &left, const auto &right) {
        return left.get().getVersion() > right.get().getVersion();
    });
}

void QORM::Schema::Creator::addRequiredCreator(const Creator &requiredCreator) {
    this->requiredCreators.emplace_back(std::ref(requiredCreator));
}

void QORM::Schema::Creator::addUpgrader(const Upgrader &upgrader) {
    this->upgraders.emplace_back(std::ref(upgrader));
    this->sortUpgraders();
}

auto QORM::Schema::Creator::getSchemaState(const Database &database,
    const std::list<QString> &existingTables) const -> Schema::State {
    if (!database.isConnected()) {
        throw std::invalid_argument("Not connected to database");
    }
    // database is considered created if the schema version table exists
    const auto created = existingTables.size() > 0;
    if (!created) {
        return Schema::State::EMPTY;
    }
    if (this->upgraders.empty()) {
        return Schema::State::UP_TO_DATE;
    }
    // TODO(aperusset) check the current version of the schema
    return Schema::State::TO_BE_UPDATED;
}

void QORM::Schema::Creator::execute(const Database &database) const {
    for (const auto &requiredCreator : this->requiredCreators) {
        requiredCreator.get().execute(database);
    }
    this->createTables(database);
    this->createViews(database);
    this->populate(database);
}

void QORM::Schema::Creator::upgradeToLatestVersion(const Database &database)
const {
    if (!database.isConnected()) {
        throw std::invalid_argument("Database is not connected");
    }
    // TODO(aperusset) do the upgrade sequentially, skip applied versions
}
