#ifndef REPOSITORIES_CRUDREPOSITORY_H_
#define REPOSITORIES_CRUDREPOSITORY_H_

#include <QSqlRecord>
#include <QString>
#include <list>
#include <memory>
#include "operations/query/update.h"
#include "operations/query/delete.h"
#include "repositories/readonlyrepository.h"

namespace QORM::Repositories {

template<class Entity, typename Key = int>
class CRUDRepository : public ReadOnlyRepository<Entity, Key> {
 public:
    explicit CRUDRepository(const Database &database,
                            Cache<Key, Entity>* const cache = nullptr) :
        ReadOnlyRepository<Entity, Key>(database, cache) {}

    virtual auto save(Entity* const entity) const -> const Key {
        const auto &assignmentsToDo = this->assignments(*entity);
        if (this->exists(entity->getKey())) {
            if (!assignmentsToDo.empty()) {
                this->getDatabase().execute(Update(this->tableName(),
                                    assignmentsToDo,
                                    this->keyCondition(entity->getKey())));
                entity->notifyChange();
            }
            return entity->getKey();
        } else {
            const auto key = this->getDatabase().insertAndRetrieveKey(
                Insert(this->tableName(), assignmentsToDo));
            entity->setKey(key);
            this->getCache().insert(key, std::unique_ptr<Entity>(entity))
                .notifyChange();
            return key;
        }
    }

    virtual void saveAll(const std::list<Entity*> &entities) const {
        for (auto *entity : entities) {
            this->save(entity);
        }
    }

    virtual void erase(const Key &key) const {
        if (this->exists(key)) {
            const auto &entity = this->get(key);
            this->getDatabase().execute(Delete(this->tableName(),
                                        this->keyCondition(key)));
            entity.notifyDelete();
            this->getCache().remove(key);
        }
    }

    virtual void eraseAll() const {
        if (const auto &allEntities = this->getAll(); !allEntities.empty()) {
            this->getDatabase().execute(Delete(this->tableName()));
            for (const auto &entity : allEntities) {
                entity.get().notifyDelete();
            }
            this->getCache().clear();
        }
    }

    // override if Entity has more fields than an auto incremented primary key
    virtual auto assignments(const Entity&) const -> std::list<Assignment> {
        return {};
    }
};

}  // namespace QORM::Repositories

#endif  // REPOSITORIES_CRUDREPOSITORY_H_
