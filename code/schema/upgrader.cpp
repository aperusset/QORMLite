#include "upgrader.h"
#include <QMutex>
#include <utility>

QORM::Schema::Upgrader::Upgrader(int version, QString description) :
    version(version), description(std::move(description)),
    upgraderMutex(QMutex::RecursionMode::Recursive) {
}

void QORM::Schema::Upgrader::execute(const Database &database) {
    const QMutexLocker lock(&this->upgraderMutex);
    if (!this->isAlreadyExecuted()) {
        this->upgrade(database);
        this->setAlreadyExecuted(true);
    }
}
