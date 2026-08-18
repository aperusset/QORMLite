#ifndef CONNECTORS_CONNECTOR_H_
#define CONNECTORS_CONNECTOR_H_

#include <QString>
#include <QSqlDatabase>
#include <memory>
#include <list>
#include <set>
#include "entities/foreignkey.h"

namespace QORM {

auto buildForeignKey(QString destinationTable,
    const QStringList &sources, const QStringList &destinations,
    const QString& onUpdate, const QString &onDelete)
-> QORM::Entities::ForeignKey;

class Database;

class Connector {
    const QString name;

 public:
    explicit Connector(QString name);
    Connector(const Connector&) = delete;
    Connector(Connector&&) = delete;
    Connector& operator=(const Connector&) = delete;
    Connector& operator=(Connector&&) = delete;
    virtual ~Connector() = default;

    auto getName() const -> const QString&;
    auto getDatabase() const -> QSqlDatabase;
    auto isConnected() const -> bool;
    virtual void connect() const;
    virtual void disconnect() const;
    virtual void preConnect() const;
    virtual void postConnect() const {}
    virtual void optimize() const {}
    virtual auto tables() const -> std::set<QString>;
    virtual auto views() const -> std::set<QString>;
    virtual auto foreignKeys(const Database&, const QString &table)
        const -> std::list<Entities::ForeignKey>;
    virtual auto connectionName() const -> QString = 0;
    virtual auto driverName() const -> QString = 0;
    virtual auto backup(const QString &fileName) const -> bool = 0;

    using UPtr = std::unique_ptr<Connector>;
};

inline auto Connector::getName() const -> const QString& {
    return this->name;
}

}  // namespace QORM

#endif  // CONNECTORS_CONNECTOR_H_
