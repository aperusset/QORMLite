#include "qormlite.h"
#include <QRecursiveMutex>
#include <map>
#include <memory>
#include <utility>

QRecursiveMutex poolMutex;
std::map<QString, std::shared_ptr<QORM::Database>> pool;

namespace {

auto initialized(const QString &name) {
    return static_cast<bool>(pool.count(name));
}

auto initializeChecks(const QORM::Connector &connector) -> QString {
    const auto databaseName = connector.getName();
    if (initialized(databaseName)) {
        throw std::logic_error("Database " + databaseName.toStdString() +
                               " is already initialized");
    }
    qDebug("Initializing database %s.", qUtf8Printable(connector.getName()));
    return databaseName;
}

}  // namespace

auto QORM::isInitialized(const QString &name) -> bool {
    const QMutexLocker lock(&poolMutex);
    return initialized(name);
}

void QORM::initialize(std::unique_ptr<Connector> connector, bool verbose) {
    const QMutexLocker lock(&poolMutex);
    const auto connectorName = initializeChecks(*connector);
    pool.try_emplace(connectorName, std::make_shared<Database>(
        std::move(connector), verbose));
}

void QORM::initialize(std::unique_ptr<Connector> connector,
        std::unique_ptr<Schema::Creator> creator,
        std::list<std::unique_ptr<Schema::Upgrader>> upgraders,
        bool verbose) {
    const QMutexLocker lock(&poolMutex);
    const auto connectorName = initializeChecks(*connector);
    pool.try_emplace(connectorName, std::make_shared<Database>(
        std::move(connector), std::move(creator), std::move(upgraders),
        verbose));
}

auto QORM::get(const QString &name) -> std::shared_ptr<Database> {
    const QMutexLocker lock(&poolMutex);
    if (!initialized(name)) {
        throw std::invalid_argument("You must initialize database " +
                                    name.toStdString() + " before using it");
    }
    return pool.at(name);
}

void QORM::destroy(const QString &name) {
    const QMutexLocker lock(&poolMutex);
    pool.erase(name);
}

void QORM::destroyAll() {
    const QMutexLocker lock(&poolMutex);
    pool.clear();
}
