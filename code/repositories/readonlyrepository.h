#ifndef REPOSITORIES_READONLYREPOSITORY_H
#define REPOSITORIES_READONLYREPOSITORY_H

#include <algorithm>
#include <list>
#include <memory>
#include <string>
#include "./cache.h"
#include "./database.h"
#include "./entity.h"
#include "./utils.h"
#include "operations/query/selection/count.h"

namespace QORM {

template<typename Key, class Entity>
class ReadOnlyRepository {
    static_assert(
        std::is_base_of<QORM::Entity<Key>, Entity>::value,
        "Entity must extend QORM::Entity");
    using EntityCreator = std::function<Entity&(const QSqlRecord&)>;

    const Database &database;
    Cache<Key, Entity> &cache;

    const EntityCreator entityCreator =
        [=](const QSqlRecord &record) -> Entity& {
            return cache.insert(
                this->buildKey(record),
                std::unique_ptr<Entity>(this->build(record)));
        };

 public:
    explicit ReadOnlyRepository(const Database &database,
                                Cache<Key, Entity> &cache) :
        database(database), cache(cache) {}
    ReadOnlyRepository(const ReadOnlyRepository&) = delete;
    ReadOnlyRepository(ReadOnlyRepository&&) = delete;
    ReadOnlyRepository& operator=(const ReadOnlyRepository&) = delete;
    ReadOnlyRepository& operator=(ReadOnlyRepository&&) = delete;
    virtual ~ReadOnlyRepository() {}

    auto getDatabase() const -> const Database& {
        return this->database;
    }

    auto getCache() const -> Cache<Key, Entity>& {
        return this->cache;
    }

    auto getEntityCreator() const -> const EntityCreator {
        return this->entityCreator;
    }

    auto qualifiedFields() const -> std::list<QString> {
        auto const tableFields = this->fields();
        auto qualifiedFields = std::list<QString>();
        std::transform(tableFields.begin(), tableFields.end(),
            std::back_inserter(qualifiedFields),
            std::bind(&Utils::qualifyFieldName, this->tableName(),
                      std::placeholders::_1));
        return qualifiedFields;
    }

    auto get(const Key &key) const -> Entity& {
        return this->cache.getOrCreate(key, [=]() -> Entity& {
            return database.entity<Entity>(
                Select(this->tableName(), this->fields())
                        .where({this->keyCondition(key)}),
                entityCreator);
        });
    }

    auto get(const std::list<Condition> &conditions) const -> Entity& {
        auto const entities = this->getAll(conditions);
        if (entities.empty()) {
            throw std::string("No entity match the given conditions");
        }
        return entities.front().get();
    }

    auto getAll() const -> std::list<std::reference_wrapper<Entity>> {
        return this->getAll({});
    }

    auto getAll(const std::list<Condition> &conditions)
        const -> std::list<std::reference_wrapper<Entity>> {
        return this->select(
            Select(this->tableName(), this->fields())
                .where(conditions));
    }

    auto select(const Select &select)
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

    virtual auto exists(const Key &key) const -> bool {
        return this->exists({this->keyCondition(key)});
    }

    virtual auto exists(const std::list<Condition> &conditions) const -> bool {
        return this->count(conditions) > 0;
    }

    virtual auto tableName() const -> QString = 0;
    virtual auto keyCondition(const Key&) const -> Condition = 0;
    virtual auto fields() const -> std::list<QString> = 0;
    virtual auto buildKey(const QSqlRecord &record) const -> Key = 0;
    virtual auto build(const QSqlRecord &record) const -> Entity* = 0;
};

}  // namespace QORM

#endif  // REPOSITORIES_READONLYREPOSITORY_H
