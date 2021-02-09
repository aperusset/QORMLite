#include "qormlite.h"
#include <QMutex>
#include <map>

QMutex poolMutex;
std::map<QString, QORMDatabase*> pool;

void QORMLite::initialize(const QString &name, const QORMCreator &creator, bool verbose, bool test) {
    const QMutexLocker lock(&poolMutex);
    if (pool.count(name)) {
        throw std::string("This database is already initialized");
    }
    qDebug("Initializing database %s in %s mode.", qUtf8Printable(name), test ? "test" : "production");
    pool.insert(std::make_pair(name, new QORMDatabase(name, creator, verbose, test)));
}

auto QORMLite::get(const QString &name) -> QORMDatabase& {
    const QMutexLocker lock(&poolMutex);
    if (!pool.count(name)) {
        throw std::string("You must initialize the database before using it");
    }
    return *pool[name];
}

void QORMLite::destroy(const QString &name) {
    const QMutexLocker lock(&poolMutex);
    if (pool.count(name)) {
        delete pool[name];
        pool.erase(name);
    }
}

void QORMLite::destroyAll() {
    const QMutexLocker lock(&poolMutex);
    for (const auto& database: pool) {
        delete database.second;
    }
    pool.clear();
}
