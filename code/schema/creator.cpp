#include "creator.h"
#include <utility>
#include "./database.h"
#include "operations/model/table.h"
#include "operations/model/view.h"

QORM::Schema::Creator::Creator(CreatorList requiredCreators) :
    requiredCreators(std::move(requiredCreators)) {
}

void QORM::Schema::Creator::execute(const Database &database) const {
    for (const auto &requiredCreator : this->requiredCreators) {
        requiredCreator->execute(database);
    }
    this->createTables(database);
    this->createViews(database);
    this->populate(database);
}
