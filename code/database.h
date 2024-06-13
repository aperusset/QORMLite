#ifndef DATABASE_H_
#define DATABASE_H_

#include <QMutex>
#include <QSqlRecord>
#include <QtSql>
#include <list>
#include <string>
#include "./creator.h"
#include "./entity.h"
#include "./utils.h"
#include "connectors/connector.h"
#include "operations/query.h"
#include "operations/query/delete.h"
#include "operations/query/insert.h"
#include "operations/query/select.h"
#include "operations/query/update.h"

namespace QORM {

class Database {
    QMutex databaseMutex;

    // TODO(aperusset) Database should take connector and creator ownership ?
    const QORM::Connector &connector;
    const QORM::Creator* const creator;
    const bool verbose;

    auto prepare(const QString&) const -> QSqlQuery;
    auto prepare(const Query&) const -> QSqlQuery;
    auto execute(QSqlQuery) const -> QSqlQuery;

 public:
    Database(const QORM::Connector&, bool verbose);
    Database(const QORM::Connector&, const QORM::Creator&, bool verbose);
    ~Database();
    Database(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(const Database&) = delete;
    Database& operator=(Database&&) = delete;

    auto getName() const -> const QString&;
    auto isVerbose() const;
    auto isConnected() const -> bool;

    /**
     * @brief connect
     * @return true if the database has been created, false if already exists
     */
    auto connect() -> bool;
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
        std::list<std::reference_wrapper<Entity>> entities;
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

inline auto Database::isVerbose() const {
    return this->verbose;
}

}  // namespace QORM

#endif  // DATABASE_H_
