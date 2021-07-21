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

    const QORM::Connector &connector;
    const QORM::Creator *creator;
    const bool verbose;

    auto prepare(const QString&) const -> QSqlQuery;
    auto prepare(const Query&) const -> QSqlQuery;
    auto execute(QSqlQuery) const -> QSqlQuery;

 public:
    explicit Database(const QORM::Connector&, bool verbose);
    Database(const QORM::Connector&, const QORM::Creator&, bool verbose);
    ~Database();
    Database(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(const Database&) = delete;
    Database& operator=(Database&&) = delete;

    auto getName() const -> QString;
    auto isVerbose() const -> bool;
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
        const std::function<Key(const QVariant&)> &keyExtractor =
            [](const QVariant &result) -> int {
                if (!result.isValid() || !result.canConvert<int>()) {
                    throw std::string("Failed to get last inserted ID as int");
                }
                return result.toInt();
            }) const -> Key {
        return keyExtractor(this->execute(insert).lastInsertId());
    }

    template<class Entity>
    auto entity(const Select &select,
                const std::function<Entity&(const QSqlRecord&)> &extractor)
    const -> Entity& {
        auto const allEntities = entities(select, extractor);
        if (allEntities.empty()) {
            throw std::string("No entity found with given query : ")
                    .append(select.generate().toStdString());
        }
        return allEntities.front().get();
    }

    template<class Entity>
    auto entities(const Select &select,
                  const std::function<Entity&(const QSqlRecord&)> &extractor)
    const -> std::list<std::reference_wrapper<Entity>> {
        std::list<std::reference_wrapper<Entity>> entities;
        auto results = this->execute(select);
        while (results.next()) {
            entities.push_back(extractor(results.record()));
        }
        return entities;
    }

    template<typename Result>
    auto result(const Select &select,
                const Result &defaultValue,
                const std::function<Result(const QSqlRecord&)> &extractor)
    const -> Result {
        auto result = this->execute(select);
        return result.next() ? extractor(result.record()) : defaultValue;
    }
};

inline auto Database::isVerbose() const -> bool {
    return this->verbose;
}

}  // namespace QORM

#endif  // DATABASE_H_
