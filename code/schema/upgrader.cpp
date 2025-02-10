#include "upgrader.h"

QORM::Schema::Upgrader::Upgrader(unsigned int version) :
    version(version) {
}

void QORM::Schema::Upgrader::execute(const Database &database) {
    if (!this->isAlreadyExecuted()) {
        this->upgrade(database);
        this->setAlreadyExecuted(true);
    }
}
