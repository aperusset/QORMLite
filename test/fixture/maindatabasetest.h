#ifndef TEST_FIXTURE_MAINDATABASETEST_H_
#define TEST_FIXTURE_MAINDATABASETEST_H_

#include <QSqlDatabase>
#include <QtTest/QtTest>

class MainDatabaseTest : public QObject {
    Q_OBJECT

    void deleteAllDatabases() {
        for (auto &connection : QSqlDatabase::connectionNames()) {
            QSqlDatabase::database(connection, false).close();
            QSqlDatabase::removeDatabase(connection);
            QFile::remove(connection);
        }
        QFile::remove(this->databaseName());
        auto const backupName = this->databaseBackupName();
        if (!backupName.isNull()) {
            QFile::remove(backupName);
        }
    }

 public:
    virtual auto databaseName() const -> QString = 0;
    virtual auto databaseBackupName() const -> QString {
        return QString();
    };

 private slots:

    void init() {
        this->deleteAllDatabases();
    }

    void cleanup() {
        this->deleteAllDatabases();
    }
};

#endif  // TEST_FIXTURE_MAINDATABASETEST_H_
