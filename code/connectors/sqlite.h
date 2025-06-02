#ifndef CONNECTORS_SQLITE_H_
#define CONNECTORS_SQLITE_H_

#include <list>
#include "./connector.h"

namespace QORM {

class SQLite : public Connector {
    const bool foreignKeysActivated;
    const bool test;

    inline static const QString TEST_PREFIX = "test_";
    inline static const QString FILE_EXTENSION = ".db";
    inline static const QString SEQUENCE_TABLE = "sqlite_sequence";

 public:
    explicit SQLite(const QString &name, bool foreignKeysActivated = true,
                    bool test = false);
    auto areForeignKeysActivated() const;
    auto isTest() const;
    void connect() const override;
    void disconnect() const override;
    void preConnect() const override;
    void postConnect() const override;
    void optimize() const override;
    auto tables() const -> std::list<QString> override;
    auto connectionName() const -> QString override;
    auto driverName() const -> QString override;
    auto backup(const QString &fileName) const -> bool override;
};

inline auto SQLite::areForeignKeysActivated() const {
    return this->foreignKeysActivated;
}

inline auto SQLite::isTest() const {
    return this->test;
}

inline auto SQLite::connectionName() const -> QString {
    return this->getName() + FILE_EXTENSION;
}

inline auto SQLite::driverName() const -> QString {
    return "QSQLITE";
}

}  // namespace QORM

#endif  // CONNECTORS_SQLITE_H_
