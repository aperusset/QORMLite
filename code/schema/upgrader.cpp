#include "upgrader.h"

QORM::Schema::Upgrader::Upgrader(int version, QString description) :
    version(version), description(description) {
}

void QORM::Schema::Upgrader::execute(const Database &database) {
    if (!this->isAlreadyExecuted()) {
        this->upgrade(database);
        this->setAlreadyExecuted(true);
    }
}
