#ifndef DATABASE_H_
#define DATABASE_H_

#include <QMutex>
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

}  // nameapce Repositories

class Database {
    using CreatorUPtr = std::unique_ptr<Schema::Creator>;
    using UpgraderUPtr = std::unique_ptr<Schema::Upgrader>;
    using UpgraderUPtrList = std::list<UpgraderUPtr>;
    using ConnectorUPtr = std::unique_ptr<Connector>;

    QMutex databaseMutex;
    const ConnectorUPtr connector;
    const CreatorUPtr creator;
    UpgraderUPtrList upgraders;
    const bool verbose;
    const std::unique_ptr<Repositories::SchemaVersionRepository> schemaVersionRepository;

    auto prepare(const QString&) const -> QSqlQuery;
    auto prepare(const Query&) const -> QSqlQuery;
    auto execute(QSqlQuery) const -> QSqlQuery;
    void createSchemaVersion();
    void create();
    void upgrade();

    template<class Selector>
    static void assertSelector() {
        static_assert(std::is_base_of<Select, Selector>::value ||
                      std::is_base_of<CTE<Select>, Selector>::value,
                      "Selector must be Select || CTE<Select>");
    }

 public:
    Database(ConnectorUPtr, bool verbose);
    Database(ConnectorUPtr, CreatorUPtr, UpgraderUPtrList, bool verbose);
    ~Database();
    Database(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(const Database&) = delete;
    Database& operator=(Database&&) = delete;

    auto getName() const -> const QString&;
    auto isVerbose() const;
    auto isConnected() const -> bool;
    auto getSchemaState() const -> Schema::State;

    void connect();
    void migrate();
    void disconnect();
    void optimize() const;
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
                        result.isValid() & result.template canConvert<Key>()) {
                    return result.toInt();
                }
                throw std::logic_error("Failed to get last id as Key");
            }) const {
        return keyExtractor(this->execute(insert));
    }

    template<class Entity, class Selector = Select>
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

    template<class Entity, class Selector = Select>
    auto entities(const Selector &selector,
            const std::function<Entity&(const QSqlRecord&)> &extractor) const {
        assertSelector<Selector>();
        RefList<Entity> entities;
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
