#ifndef QORMDATABASE_H
#define QORMDATABASE_H

#include <QtSql>
#include <QSqlRecord>
#include <QMutex>
#include <string>
#include <list>
#include "qormcreator.h"
#include "qormentity.h"
#include "qormutils.h"
#include "operations/query.h"
#include "operations/query/insert.h"
#include "operations/query/select.h"
#include "operations/query/update.h"
#include "operations/query/delete.h"

class QORMDatabase {

    QMutex databaseMutex;

    const QString name;
    const QORMCreator &creator;
    const bool verbose;
    const bool test;

    auto prepare(const QString&) const -> QSqlQuery;
    auto prepare(const Query&) const -> QSqlQuery;
    auto execute(QSqlQuery) const -> QSqlQuery;

    static const QString TEST_PREFIX;
    static const QString FILE_EXTENSION;

public:
    QORMDatabase(const QString &name, const QORMCreator&, bool verbose, bool test);
    ~QORMDatabase();
    QORMDatabase(const QORMDatabase&) = delete;
    QORMDatabase& operator=(const QORMDatabase) = delete;

    auto getName() const -> QString;
    auto isVerbose() const -> bool;
    auto isTest() const -> bool;
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

    auto exists(const QString &table, const std::list<Condition>&) const -> bool;

    template<typename Key = int>
    auto insertAndRetrieveKey(const Insert &insert,
        const std::function<Key(const QVariant&)> &keyExtractor =
            [](const QVariant &result) -> int {
                if (!result.isValid() || !result.canConvert<int>()) {
                    throw std::string("Failed to retrieve last inserted ID as integer");
                }
                return result.toInt();
            }
    ) const -> Key {
        return keyExtractor(this->execute(insert).lastInsertId());
    }

    template<class Entity>
    auto entity(
        const Select &select,
        const std::function<Entity&(const QSqlRecord&)> &extractor
    ) const -> Entity& {
        auto const allEntities = entities(select, extractor);
        if (allEntities.empty()) {
            throw std::string("No entity found with given query : ") + select.generate().toStdString();
        }
        return allEntities.front().get();
    }

    template<class Entity>
    auto entities(
        const Select &select,
        const std::function<Entity&(const QSqlRecord&)> &extractor
    ) const -> std::list<std::reference_wrapper<Entity>> {
        std::list<std::reference_wrapper<Entity>> entities;
        auto results = this->execute(select);
        while (results.next()) {
            entities.push_back(extractor(results.record()));
        }
        return entities;
    }

    template<typename Result>
    auto result(
        const Select &select,
        const Result &defaultValue,
        const std::function<Result(const QSqlRecord&)> &extractor
    ) const -> Result {
        auto result = this->execute(select);
        return result.next() ? extractor(result.record()) : defaultValue;
    }
};

#endif // QORMDATABASE_H
