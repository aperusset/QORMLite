#ifndef QORMDATABASE_H
#define QORMDATABASE_H

#include <QtSql>
#include "qormcreator.h"
#include "qormentity.h"
#include "operations/query.h"
#include "operations/query/select.h"

class QORMDatabase {

    const QString name;
    const QORMCreator &creator;
    const bool verbose;
    const bool test;

    auto prepare(const QString&) const -> QSqlQuery;
    auto prepare(const Query&) const -> QSqlQuery;
    auto execute(QSqlQuery) const -> QSqlQuery;

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
    //auto referenced(const QString &sourceTable, const QString &destinationTable) const -> bool;

     /* TODO (templated functions ?, db creator needed)
      * isReferenced
      * insertAndRetrieveId -> lastInsertedId needed ?
      * select to return a list of entities
      * select to return a result or a default value
      * printQuery for verbose mode
      */
};

#endif // QORMDATABASE_H
