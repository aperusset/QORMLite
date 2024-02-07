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
                            Cache<Key, Entity> &cache) :
        ReadOnlyRepository<Key, Entity> (database, cache) {}

    virtual auto save(Entity* const entity) const -> Key {
        auto const assignementsToDo = this->assignements(*entity);
        if (this->existsByKey(entity->getKey())) {
            if (!assignementsToDo.empty()) {
                this->getDatabase().execute(QORM::Update(this->tableName(),
                                    assignementsToDo,
                                    this->keyCondition(entity->getKey())));
            }
        } else {
            auto const key = this->getDatabase().insertAndRetrieveKey(
                QORM::Insert(this->tableName(), assignementsToDo));
            entity->setKey(key);
            this->getCache().insert(key, std::unique_ptr<Entity>(entity));
        }
        entity->notifyChange();
        return entity->getKey();
    }

    virtual void erase(const Key &key) const {
        if (this->existsByKey(key)) {
            auto const &entity = this->getByKey(key);
            this->getDatabase().execute(QORM::Delete(this->tableName(),
                                        this->keyCondition(key)));
            entity.notifyDelete();
            this->getCache().remove(key);
        }
    }

    virtual auto assignements(const Entity&)
        const -> std::list<QORM::Assignment> {
            return {};
        }
};

}  // namespace QORM

#endif  // REPOSITORIES_CRUDREPOSITORY_H_
