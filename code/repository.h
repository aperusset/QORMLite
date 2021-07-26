#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include <QSqlRecord>
#include <QString>
#include <list>
#include <memory>
#include "./entity.h"
#include "./database.h"
#include "./cache.h"
#include "operations/query/select.h"
#include "operations/query/update.h"
#include "operations/query/delete.h"
#include "operations/query/condition/condition.h"
#include "operations/query/selection/count.h"

namespace QORM {

template<typename Key, class Entity>
class Repository {
    static_assert(
        std::is_base_of<QORM::Entity<Key>, Entity>::value,
        "Entity must extend QORM::Entity");

    const Database &database;
    Cache<Key, Entity> &cache;

    const std::function<Entity&(const QSqlRecord&)> entityCreator =
        [=](const QSqlRecord &record) -> Entity& {
            return cache.insert(
                this->buildKey(record),
                std::unique_ptr<Entity>(this->build(record)));
        };

 public:
    explicit Repository(const Database &database, Cache<Key, Entity> &cache) :
        database(database), cache(cache) {}
    Repository(const Repository&) = delete;
    Repository(Repository&&) = delete;
    Repository& operator=(const Repository&) = delete;
    Repository& operator=(Repository&&) = delete;
    virtual ~Repository() {}

    auto getDatabase() const -> const Database& {
        return this->database;
    }

    auto getByKey(const Key &key) const -> Entity& {
        return this->cache.getOrCreate(key, [=]() -> Entity& {
            return database.entity<Entity>(
                Select(this->tableName(), this->fields())
                        .where({this->keyCondition(key)}),
                entityCreator);
        });
    }

    auto getAll() const -> std::list<std::reference_wrapper<Entity>> {
        return this->getAll(Select(this->tableName(), this->fields()));
    }

    auto getAll(const Select &select)
        const -> std::list<std::reference_wrapper<Entity>> {
        return database.entities<Entity>(select, entityCreator);
    }

    auto count() const -> size_t {
        return this->count({});
    }

    virtual auto count(const std::list<Condition> &conditions) const -> size_t {
        auto const total = "total";
        return database.result<size_t>(
            Select(this->tableName(), {Count("*", total)})
                    .where(conditions), 0,
            [&total](const QSqlRecord &record) -> size_t {
                return record.value(total).toUInt();
            });
    }

    virtual auto existsByKey(const Key &key) const -> bool {
        return this->exists({this->keyCondition(key)});
    }

    virtual auto exists(const std::list<Condition> &conditions) const -> bool {
        return this->count(conditions) > 0;
    }

    virtual auto save(Entity* const entity) const -> Key {
        if (this->existsByKey(entity->getKey())) {
            auto const assignementsToDo = this->assignements(*entity);
            if (!assignementsToDo.empty()) {
                database.execute(QORM::Update(this->tableName(),
                                    assignementsToDo,
                                    this->keyCondition(entity->getKey())));
            }
        } else {
            this->cache.insert(this->insert(*entity),
                               std::unique_ptr<Entity>(entity));
        }
        entity->notifyChange();
        return entity->getKey();
    }

    virtual void erase(const Key &key) const {
        if (this->existsByKey(key)) {
            auto const &entity = this->getByKey(key);
            database.execute(QORM::Delete(this->tableName(),
                                          this->keyCondition(key)));
            entity.notifyDelete();
            this->cache.remove(key);
        }
    }

    virtual auto tableName() const -> QString = 0;
    virtual auto keyCondition(const Key&) const -> Condition = 0;
    virtual auto fields() const -> std::list<QString> = 0;
    virtual auto buildKey(const QSqlRecord &record) const -> Key = 0;
    virtual auto build(const QSqlRecord &record) const -> Entity* = 0;
    virtual auto insert(Entity&) const -> Key = 0;
    virtual auto assignements(const Entity&)
        const -> std::list<QORM::Assignment> {
            return {};
        }
};

}  // namespace QORM

#endif  // REPOSITORY_H_
