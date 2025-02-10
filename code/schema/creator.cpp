#include "creator.h"
#include <QMutex>
#include <utility>
#include "./database.h"

QMutex creatorMutex;

QORM::Schema::Creator::Creator(CreatorList requiredCreators) :
    requiredCreators(std::move(requiredCreators)) {
}

void QORM::Schema::Creator::addRequiredCreator(CreatorSPtr creator) {
    this->requiredCreators.emplace_back(std::move(creator));
}

void QORM::Schema::Creator::execute(const Database &database) {
    const QMutexLocker lock(&creatorMutex);
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
