#include "upgrader.h"
#include <QMutex>
#include <utility>

QMutex upgraderMutex;

QORM::Schema::Upgrader::Upgrader(int version, QString description) :
    version(version), description(std::move(description)) {
}

void QORM::Schema::Upgrader::execute(const Database &database) {
    const QMutexLocker lock(&upgraderMutex);
    if (!this->isAlreadyExecuted()) {
        this->upgrade(database);
        this->setAlreadyExecuted(true);
    }
}
