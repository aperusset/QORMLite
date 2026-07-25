#ifndef REPOSITORIES_CRUDREPOSITORY_H_
#define REPOSITORIES_CRUDREPOSITORY_H_

#include <QSqlRecord>
#include <QString>
#include <list>
#include <memory>
#include <utility>
#include "operations/query/insert.h"
#include "operations/query/update.h"
#include "operations/query/delete.h"
#include "repositories/readonlyrepository.h"

namespace QORM::Repositories {

template<typename Entity>
class CRUDRepository : public ReadOnlyRepository<Entity> {
    using Key = typename Entity::KeyType;

 public:
    using ReadOnlyRepository<Entity>::ReadOnlyRepository;

    virtual auto create(typename Entity::UPtr entity) const -> Entity& {
        entity->key = this->getDatabase().insertAndRetrieveKey(
                Insert(this->tableName(), this->assignments(*entity)));
        auto &cached = this->getCache().upsert(entity->key, std::move(entity));
        cached.notifyChange();
        return cached;
    }

    template<typename... EntityArgs>
    auto create(EntityArgs&&... args) const -> Entity& {
        return this->create(
            std::make_unique<Entity>(std::forward<EntityArgs>(args)...));
    }

    virtual void update(const Entity &entity) const {
        const auto &assignmentsToDo = this->assignments(entity);
        if (!assignmentsToDo.empty()) {
            this->getDatabase().execute(Update(this->tableName(),
                assignmentsToDo, this->keyCondition(entity.getKey())));
        }
        entity.notifyChange();
    }

    virtual void erase(const Key &key) const {
        if (this->exists(key)) {
            const auto &entity = this->get(key);
            this->getDatabase().execute(Delete(this->tableName(),
                                        this->keyCondition(key)));
            this->getCache().invalidate(key);
            entity.notifyDelete();
            this->getCache().remove(key);
        }
    }

    virtual void eraseAll() const {
        if (const auto &allEntities = this->getAll(); !allEntities.empty()) {
            this->getDatabase().execute(Delete(this->tableName()));
            this->getCache().invalidateAll();
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
