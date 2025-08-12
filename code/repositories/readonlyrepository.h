#ifndef REPOSITORIES_READONLYREPOSITORY_H
#define REPOSITORIES_READONLYREPOSITORY_H

#include <algorithm>
#include <list>
#include <memory>
#include "./cache.h"
#include "./database.h"
#include "./utils.h"
#include "entities/baseentity.h"
#include "operations/query/cte.h"
#include "operations/query/selection/count.h"
#include "operations/query/condition/equals.h"

namespace QORM::Repositories {

template<class Entity, typename Key = int>
class ReadOnlyRepository {
    static_assert(
        std::is_base_of<Entities::BaseEntity<Key>, Entity>::value,
        "Entity must extend QORM::Entities::BaseEntity");
    using EntityCreator = std::function<Entity&(const QSqlRecord&)>;
    using EntityCache = Cache<Key, Entity>;
    inline static const QString DEFAULT_KEY_NAME = "id";

    const Database &database;
    const std::unique_ptr<EntityCache> cache;

    const EntityCreator entityCreator =
        [this](const auto &record) -> Entity& {
            return this->cache.get()->insert(
                this->buildKey(record), this->build(record));
        };

 public:
    explicit ReadOnlyRepository(const Database &database,
                                Cache<Key, Entity>* const cache = nullptr) :
        database(database),
        cache(cache == nullptr ? std::make_unique<EntityCache>()
                               : std::unique_ptr<EntityCache>(cache)) {}
    ReadOnlyRepository(const ReadOnlyRepository&) noexcept = delete;
    ReadOnlyRepository(ReadOnlyRepository&&) noexcept = delete;
    ReadOnlyRepository& operator=(const ReadOnlyRepository&) = delete;
    ReadOnlyRepository& operator=(ReadOnlyRepository&&) = delete;
    virtual ~ReadOnlyRepository() {}

    auto getDatabase() const -> const Database& {
        return this->database;
    }

    auto getCache() const -> EntityCache& {
        return *this->cache.get();
    }

    auto getEntityCreator() const -> const EntityCreator& {
        return this->entityCreator;
    }

    auto qualifiedFields() const {
        const auto tableFields = this->fields();
        std::list<QString> qualifiedFields;
        std::transform(tableFields.begin(), tableFields.end(),
            std::back_inserter(qualifiedFields),
            std::bind(&Utils::qualifyFieldName, this->tableName(),
                      std::placeholders::_1));
        return qualifiedFields;
    }

    auto get(const Key &key) const -> Entity& {
        return this->cache.get()->getOrCreate(key, [=]() -> Entity& {
            return database.entity(Select(this->tableName(), this->fields())
                    .where({this->keyCondition(key)}), entityCreator);
        });
    }

    auto get(const std::list<Condition> &conditions) const -> Entity& {
        if (const auto entities = this->getAll(conditions); !entities.empty()) {
            return entities.front().get();
        }
        throw std::logic_error("No entity match the given conditions");
    }

    auto getAll(const std::list<Order> &orders = {}) const {
        return this->getAll({}, orders);
    }

    auto getAll(const std::list<Condition> &conditions,
                const std::list<Order> &orders = {}) const {
        return this->select(
            Select(this->tableName(), this->fields())
                .where(conditions)
                .orderBy(orders));
    }

    auto select(const Select &select) const {
        return database.entities(select, entityCreator);
    }

    auto select(const CTE<Select> &cte) const {
        return database.entities(cte, entityCreator);
    }

    auto count() const -> size_t {
        return this->count({});
    }

    virtual auto count(const std::list<Condition> &conditions) const -> size_t {
        const auto total = "total";
        return database.result<size_t>(
            Select(this->tableName(), {Count(Selection::ALL, total)})
                    .where(conditions), 0,
            [&total](const auto &record) -> size_t {
                return record.value(total).toUInt();
            });
    }

    virtual auto exists(const Key &key) const -> bool {
        return this->cache.get()->contains(key) ||
               this->exists({this->keyCondition(key)});
    }

    virtual auto exists(const std::list<Condition> &conditions) const -> bool {
        return this->count(conditions) > 0;
    }

    void assertFieldValidity(const QString &field) const {
        if (!Utils::contains(this->fields(), field) &&
            !Utils::contains(this->qualifiedFields(), field)) {
            throw std::logic_error(field.toStdString() +
                " field is not part of " +
                this->tableName().toStdString() + " table");
        }
    }

    virtual auto keyName() const -> QString {
        return DEFAULT_KEY_NAME;
    }

    virtual auto keyCondition(const Key &key) const -> Condition {
        if constexpr (std::is_integral<Key>::value) {
            return Equals::field(this->keyName(), key);
        }
        throw std::runtime_error("keyCondition must be overriden");
    }

    virtual auto buildKey(const QSqlRecord &record) const -> Key {
        if constexpr (std::is_integral<Key>::value) {
            return Utils::getIntOrThrow(record, this->keyName());
        }
        throw std::runtime_error("buildKey must be overriden");
    }

    virtual auto tableName() const -> QString = 0;
    virtual auto fields() const -> std::list<QString> = 0;
    virtual auto build(const QSqlRecord &record)
        const -> std::unique_ptr<Entity> = 0;
};

}  // namespace QORM::Repositories

#endif  // REPOSITORIES_READONLYREPOSITORY_H
