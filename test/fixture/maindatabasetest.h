#ifndef TEST_FIXTURE_MAINDATABASETEST_H_
#define TEST_FIXTURE_MAINDATABASETEST_H_

#include <QSqlDatabase>
#include <QTest>
#include "./database.h"
#include "fixture/testconnector.h"
#include "fixture/testcreator.h"

class MainDatabaseTest : public QObject {
    Q_OBJECT

 public:
    virtual auto databaseName() const -> QString = 0;
    virtual auto databaseBackupName() const -> QString {
        return QString();
    };

    virtual auto databaseWithCreator(
            std::list<std::unique_ptr<QORM::Schema::Upgrader>> upgraders = {},
            bool verbose = false) -> QORM::Database {
        return QORM::Database(
            std::make_unique<TestConnector>(this->databaseName()),
            std::make_unique<TestCreator>(), std::move(upgraders), verbose);
    }

    virtual auto databaseWithoutCreator(
            bool verbose = false) -> QORM::Database {
        return QORM::Database(
            std::make_unique<TestConnector>(this->databaseName()),
            verbose);
    }

    void deleteAllDatabases() {
        for (auto &connection : QSqlDatabase::connectionNames()) {
            QSqlDatabase::database(connection, false).close();
            QSqlDatabase::removeDatabase(connection);
            QFile::remove(connection);
        }
        QFile::remove(this->databaseName());
        const auto backupName = this->databaseBackupName();
        if (!backupName.isNull()) {
            QFile::remove(backupName);
        }
    }
};

#endif  // TEST_FIXTURE_MAINDATABASETEST_H_
