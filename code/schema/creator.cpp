#include "creator.h"
#include <utility>
#include "./database.h"

QORM::Schema::Creator::Creator(CreatorList requiredCreators) :
    creatorMutex(QMutex::RecursionMode::Recursive),
    requiredCreators(std::move(requiredCreators)) {
}

void QORM::Schema::Creator::addRequiredCreator(CreatorSPtr creator) {
    this->requiredCreators.emplace_back(std::move(creator));
}

void QORM::Schema::Creator::execute(const Database &database) {
    const QMutexLocker lock(&this->creatorMutex);
    if (!this->isAlreadyExecuted()) {
        for (const auto &requiredCreator : this->requiredCreators) {
            requiredCreator->execute(database);
        }
        this->createTables(database);
        this->createViews(database);
        this->populate(database);
        this->setAlreadyExecuted(true);
    }
}
