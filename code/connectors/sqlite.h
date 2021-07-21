#ifndef SQLITE_H_
#define SQLITE_H_

#include "connector.h"

namespace QORM {

class SQLite : public Connector {
    const bool test;
    const bool foreignKeysActivated;

    static const QString TEST_PREFIX;
    static const QString FILE_EXTENSION;

 public:
    SQLite(const QString &name, bool test, bool foreignKeysActivated = true);
    auto isTest() const -> bool;
    auto areForeignKeysActivated() const -> bool;
    void disconnect() const override;
    void preConnect() const override;
    void postConnect() const override;
    void optimize() const override;
    auto tables() const -> std::list<QString> override;
    auto driverName() const -> QString override;
    auto backup(const QString &fileName) const -> bool override;
};

inline auto SQLite::isTest() const -> bool {
    return this->test;
}

inline auto SQLite::areForeignKeysActivated() const -> bool {
    return this->foreignKeysActivated;
}

inline auto QORM::SQLite::driverName() const -> QString {
    return "QSQLITE";
}

}  // namespace QORM

#endif // SQLITE_H_
