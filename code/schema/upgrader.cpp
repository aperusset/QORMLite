#include "upgrader.h"
#include <QMutexLocker>
#include <utility>

QORM::Schema::Upgrader::Upgrader(int version, QString description) :
    version(version), description(std::move(description)) {
}

void QORM::Schema::Upgrader::execute(const Database &database) {
    QMutexLocker lock(&this->upgraderMutex);
    if (!this->isAlreadyExecuted()) {
        this->upgrade(database);
        this->setAlreadyExecuted(true);
    }
}
