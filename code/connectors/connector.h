#ifndef CONNECTOR_H_
#define CONNECTOR_H_

#include <QString>
#include <QSqlDatabase>
#include <list>

namespace QORM {

class Database;

class Connector {
    const QString name;

 public:
    explicit Connector(QString name);
    Connector(const Connector&) = delete;
    Connector(Connector&&) = delete;
    Connector& operator=(const Connector&) = delete;
    Connector& operator=(Connector&&) = delete;
    virtual ~Connector() {}

    auto getName() const -> QString;
    auto getDatabase() const -> QSqlDatabase;
    auto isConnected() const -> bool;
    virtual void connect() const;
    virtual void disconnect() const;
    virtual void preConnect() const;
    virtual void postConnect() const {}
    virtual void optimize() const {}
    virtual auto tables() const -> std::list<QString>;
    virtual auto views() const -> std::list<QString>;
    virtual auto databaseName() const -> QString {
        return this->getName();
    }
    virtual auto driverName() const -> QString = 0;
    virtual auto backup(const QString &fileName) const -> bool = 0;
};

inline auto Connector::getName() const -> QString {
    return this->name;
}

}  // namespace QORM

#endif  // CONNECTOR_H_
