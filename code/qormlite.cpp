#include "qormlite.h"
#include <QMutex>
#include <map>
#include <utility>
#include <string>

QMutex poolMutex;
std::map<QString, QORM::Database*> pool;

auto QORM::isInitialized(const QString &name) -> bool {
    return pool.count(name);
}

void QORM::initialize(const Connector &connector, const Creator &creator, bool verbose) {
    const QMutexLocker lock(&poolMutex);
    if (isInitialized(connector.getName())) {
        throw std::string("This database is already initialized");
    }
    qDebug("Initializing database %s.", qUtf8Printable(connector.getName()));
    pool.insert(std::make_pair(
        connector.getName(), new Database(connector, creator, verbose)));
}

auto QORM::get(const QString &name) -> Database& {
    const QMutexLocker lock(&poolMutex);
    if (!isInitialized(name)) {
        throw std::string("You must initialize the database before using it");
    }
    return *pool[name];
}

void QORM::destroy(const QString &name) {
    const QMutexLocker lock(&poolMutex);
    if (isInitialized(name)) {
        delete pool[name];
        pool.erase(name);
    }
}

void QORM::destroyAll() {
    const QMutexLocker lock(&poolMutex);
    for (const auto &database : pool) {
        delete database.second;
    }
    pool.clear();
}
