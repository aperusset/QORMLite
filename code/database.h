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

    auto prepare(const QString&) const -> QSqlQuery;
    auto prepare(const Query&) const -> QSqlQuery;
    auto execute(QSqlQuery) const -> QSqlQuery;
    void createSchemaVersion();
    void create();
    void upgrade();
    auto schemaVersionRepository() const ->
        const Repositories::SchemaVersionRepository&;

 public:
    Database(ConnectorUPtr, bool verbose);
    Database(ConnectorUPtr, CreatorUPtr, UpgraderUPtrList, bool verbose);
    ~Database();
    Database(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(const Database&) = delete;
    Database& operator=(Database&&) = delete;

    auto getName() const -> const QString&;
    auto getCreator() const -> Schema::Creator&;
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

    template<class Entity>
    auto entity(const Select &select,
                const std::function<Entity&(const QSqlRecord&)> &extractor)
    const -> Entity& {
        if (const auto all = entities(select, extractor); !all.empty()) {
            return all.front().get();
        }
        throw std::logic_error("No entity found with given query : " +
                               select.generate().toStdString());
    }

    template<class Entity>
    auto entities(const Select &select,
            const std::function<Entity&(const QSqlRecord&)> &extractor) const {
        RefList<Entity> entities;
        auto qSqlQuery = this->execute(select);
        while (qSqlQuery.next()) {
            entities.push_back(extractor(qSqlQuery.record()));
        }
        return entities;
    }

    template<typename Result>
    auto result(const Select &select, const Result &defaultValue,
            const std::function<Result(const QSqlRecord&)> &extractor) const {
        if (const auto all = results(select, extractor); !all.empty()) {
            return all.front();
        }
        return defaultValue;
    }

    template<typename Result>
    auto results(const Select &select,
            const std::function<Result(const QSqlRecord&)> &extractor) const {
        std::list<Result> results;
        auto qSqlQuery = this->execute(select);
        while (qSqlQuery.next()) {
            results.push_back(extractor(qSqlQuery.record()));
        }
        return results;
    }
};

inline auto Database::getCreator() const -> Schema::Creator& {
    return *this->creator.get();
}

inline auto Database::isVerbose() const {
    return this->verbose;
}

}  // namespace QORM

#endif  // DATABASE_H_
