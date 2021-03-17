#include "qormlite.h"
#include <QMutex>
#include <map>
#include <utility>
#include <string>

namespace {

QMutex poolMutex;
std::map<QString, QORM::Database*> pool;

}  // namespace

auto QORM::isInitialized(const QString &name) -> bool {
    return pool.count(name);
}

void QORM::initialize(const QString &name, const Creator &creator,
                      bool verbose, bool test) {
    const QMutexLocker lock(&poolMutex);
    if (isInitialized(name)) {
        throw std::string("This database is already initialized");
    }
    qDebug(
        "Initializing database %s in %s mode.",
        qUtf8Printable(name), test ? "test" : "production");
    pool.insert(std::make_pair(
        name, new Database(name, creator, verbose, test)));
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
