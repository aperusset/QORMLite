#ifndef DATABASE_H_
#define DATABASE_H_

#include <QRecursiveMutex>
#include <QSqlError>
#include <QSqlRecord>
#include <list>
#include <memory>
#include "connectors/connector.h"
#include "entities/baseentity.h"
#include "operations/query.h"
#include "operations/query/cte.h"
#include "operations/query/insert.h"
#include "operations/query/select.h"
#include "schema/creator.h"
#include "schema/upgrader.h"
#include "schema/state.h"

namespace QORM {

namespace Repositories {

class SchemaVersionRepository;

}  // namespace Repositories

class Database {
    mutable QRecursiveMutex databaseMutex;
    const Connector::UPtr connector;
    const Schema::Creator::UPtr creator;
    Schema::Upgrader::UPtrList upgraders;
    const bool verbose;
    const std::unique_ptr<Repositories::SchemaVersionRepository> svRepository;

    auto prepare(const QString&) const -> QSqlQuery;
    auto prepare(const Query&) const -> QSqlQuery;
    auto execute(QSqlQuery) const -> QSqlQuery;
    void createSchemaVersion() const;
    void create();
    void upgrade();
    void registerUpgrade(const Schema::Upgrader&) const;

    template<typename Selector>
    static void assertSelector() {
        static_assert(std::is_base_of_v<Select, Selector> ||
                      std::is_base_of_v<CTE<Select>, Selector>,
                      "Selector must be Select or CTE<Select>");
    }

 public:
    Database(Connector::UPtr, bool verbose);
    Database(Connector::UPtr, Schema::Creator::UPtr, Schema::Upgrader::UPtrList,
             bool verbose);
    ~Database();
    Database(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(const Database&) = delete;
    Database& operator=(Database&&) = delete;

    auto getName() const -> const QString&;
    auto isVerbose() const;
    auto isConnected() const -> bool;
    auto getSchemaState() const -> Schema::State;


    void connect() const;
    void migrate();
    void disconnect() const;
    void optimize() const;
    auto foreignKeys(const QString &table)
        const -> std::list<Entities::ForeignKey>;

    auto backup(const QString &fileName) -> bool;
    auto execute(const QString&) const -> QSqlQuery;
    auto execute(const Query&) const -> QSqlQuery;
    auto exists(const QString &table,
                const std::list<Condition>&) const -> bool;

    template<typename Key = int>
    auto insertAndRetrieveKey(const Insert &insert,
        const std::function<Key(const QSqlQuery&)> &keyExtractor =
            [](const auto &query) -> Key {
                if (const auto &result = query.lastInsertId();
                        result.isValid() && result.template canConvert<Key>()) {
                    return result.template value<Key>();
                }
                throw std::logic_error("Failed to get last id as Key");
            }) const {
        return keyExtractor(this->execute(insert));
    }

    template<typename Entity, typename Selector = Select>
    auto entity(const Selector &selector,
                const std::function<Entity&(const QSqlRecord&)> &extractor)
    const -> Entity& {
        assertSelector<Selector>();
        if (const auto all = entities(selector, extractor); !all.empty()) {
            return all.front().get();
        }
        throw std::logic_error("No entity found with given query : " +
                               selector.generate().toStdString());
    }

    template<typename Entity, typename Selector = Select>
    auto entities(const Selector &selector,
            const std::function<Entity&(const QSqlRecord&)> &extractor) const {
        assertSelector<Selector>();
        using Key = typename Entity::KeyType;
        typename Entities::BaseEntity<Entity, Key>::RefList entities;
        auto qSqlQuery = this->execute(selector);
        while (qSqlQuery.next()) {
            entities.push_back(extractor(qSqlQuery.record()));
        }
        return entities;
    }

    template<typename Result, class Selector = Select>
    auto result(const Selector &selector, const Result &defaultValue,
            const std::function<Result(const QSqlRecord&)> &extractor) const {
        assertSelector<Selector>();
        if (const auto all = results(selector, extractor); !all.empty()) {
            return all.front();
        }
        return defaultValue;
    }

    template<typename Result, class Selector = Select>
    auto results(const Selector &selector,
            const std::function<Result(const QSqlRecord&)> &extractor) const {
        assertSelector<Selector>();
        std::list<Result> results;
        auto qSqlQuery = this->execute(selector);
        while (qSqlQuery.next()) {
            results.push_back(extractor(qSqlQuery.record()));
        }
        return results;
    }
};

inline auto Database::isVerbose() const {
    return this->verbose;
}

}  // namespace QORM

#endif  // DATABASE_H_
