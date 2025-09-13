#include "upgrader.h"
#include <QMutexLocker>
#include <utility>

QORM::Schema::Upgrader::Upgrader(int version, QString description,
                                 bool delayDataMigration) :
    version(version), description(std::move(description)),
    delayDataMigration(delayDataMigration) {
}

void QORM::Schema::Upgrader::execute(const Database &database) {
    QMutexLocker lock(&this->upgraderMutex);
    if (!this->isAlreadyExecuted()) {
        this->upgradeSchema(database);
        if (!this->delayDataMigration) {
            this->migrateData(database);
        }
        this->setAlreadyExecuted(true);
    }
}

void QORM::Schema::Upgrader::executeDelayed(const Database &database) {
    QMutexLocker lock(&this->upgraderMutex);
    if (this->isAlreadyExecuted() && this->delayDataMigration) {
        this->migrateData(database);
    }
}
