#ifndef REPOSITORIES_CRUDREPOSITORY_H_
#define REPOSITORIES_CRUDREPOSITORY_H_

#include <QSqlRecord>
#include <QString>
#include <list>
#include <memory>
#include <stdexcept>
#include <utility>
#include "operations/query/insert.h"
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

    [[deprecated("Use create(std::unique_ptr) or update(&) instead")]]
    virtual auto save(Entity* const entity) const -> Key {
        if (entity == nullptr) {
            throw std::invalid_argument("Cannot save nullptr");
        }
        if (this->exists(entity->getKey())) {
            this->update(*entity);
            return entity->getKey();
        } else {
            return this->create(std::unique_ptr<Entity>(entity)).getKey();
        }
    }

    virtual auto create(std::unique_ptr<Entity> entity) const -> Entity& {
        const auto key = this->getDatabase().insertAndRetrieveKey(
                Insert(this->tableName(), this->assignments(*entity)));
        entity->setKey(key);
        auto &cachedEntity = this->getCache().insert(key, std::move(entity));
        cachedEntity.notifyChange();
        return cachedEntity;
    }

    virtual void update(const Entity &entity) const {
        const auto &assignmentsToDo = this->assignments(entity);
        if (!assignmentsToDo.empty()) {
            this->getDatabase().execute(Update(this->tableName(),
                assignmentsToDo, this->keyCondition(entity.getKey())));
        }
        entity.notifyChange();
    }

    virtual void saveAll(const std::list<Entity*> &entities) const {
        for (auto *entity : entities) {
            if (entity != nullptr) {
                if (this->exists(entity->getKey())) {
                    this->update(*entity);
                } else {
                    this->create(std::unique_ptr<Entity>(entity));
                }
            }
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
