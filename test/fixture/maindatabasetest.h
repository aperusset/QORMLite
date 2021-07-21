#ifndef MAINDATABASETEST_H
#define MAINDATABASETEST_H

#include <QtTest/QtTest>
#include <QSqlDatabase>

class MainDatabaseTest : public QObject {

    Q_OBJECT

    void deleteAllDatabases() {
        for(auto &connection : QSqlDatabase::connectionNames()) {
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

#endif // MAINDATABASETEST_H
