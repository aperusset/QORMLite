#ifndef REPOSITORIES_CRUDREPOSITORY_H_
#define REPOSITORIES_CRUDREPOSITORY_H_

#include <QSqlRecord>
#include <QString>
#include <list>
#include <memory>
#include "./entity.h"
#include "operations/query/update.h"
#include "operations/query/delete.h"
#include "repositories/readonlyrepository.h"

namespace QORM {

template<typename Key, class Entity>
class CRUDRepository : public ReadOnlyRepository<Key, Entity> {
 public:
    explicit CRUDRepository(const Database &database,
                            Cache<Key, Entity>* const cache = nullptr) :
        ReadOnlyRepository<Key, Entity> (database, cache) {}

    virtual auto save(Entity* const entity) const -> const Key& {
        auto const assignmentsToDo = this->assignments(*entity);
        if (this->exists(entity->getKey())) {
            if (!assignmentsToDo.empty()) {
                this->getDatabase().execute(QORM::Update(this->tableName(),
                                    assignmentsToDo,
                                    this->keyCondition(entity->getKey())));
            }
        } else {
            auto const key = this->getDatabase().insertAndRetrieveKey(
                QORM::Insert(this->tableName(), assignmentsToDo));
            entity->setKey(key);
            this->getCache().insert(key, std::unique_ptr<Entity>(entity));
        }
        entity->notifyChange();
        return entity->getKey();
    }

    virtual void saveAll(const std::list<Entity*> &entities) const {
        for (auto const entity : entities) {
            this->save(entity);
        }
    }

    virtual void erase(const Key &key) const {
        if (this->exists(key)) {
            auto const &entity = this->get(key);
            this->getDatabase().execute(QORM::Delete(this->tableName(),
                                        this->keyCondition(key)));
            entity.notifyDelete();
            this->getCache().remove(key);
        }
    }

    virtual void eraseAll() const {
        auto const allEntities = this->getAll();
        if (!allEntities.empty()) {
            this->getDatabase().execute(QORM::Delete(this->tableName()));
            for (auto const entity : allEntities) {
                entity.get().notifyDelete();
            }
            this->getCache().clear();
        }
    }

    // override if Entity has more fields than an auto incremented primary key
    virtual auto assignments(const Entity&)
        const -> std::list<QORM::Assignment> {
            return {};
        }
};

}  // namespace QORM

#endif  // REPOSITORIES_CRUDREPOSITORY_H_
