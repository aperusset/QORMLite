#include "upgrader.h"

void QORM::Schema::Upgrader::execute(const Database &database) {
    if (!this->isAlreadyExecuted()) {
        this->upgrade(database);
        this->setAlreadyExecuted(true);
    }
}
