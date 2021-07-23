#ifndef SQLITE_H_
#define SQLITE_H_

#include <list>
#include "./connector.h"

namespace QORM {

class SQLite : public Connector {
    const bool foreignKeysActivated;
    const bool test;

    static const QString TEST_PREFIX;
    static const QString FILE_EXTENSION;
    static const QString SEQUENCE_TABLE;

 public:
    explicit SQLite(const QString &name, bool foreignKeysActivated = true,
                    bool test = false);
    auto areForeignKeysActivated() const -> bool;
    auto isTest() const -> bool;
    void disconnect() const override;
    void preConnect() const override;
    void postConnect() const override;
    void optimize() const override;
    auto tables() const -> std::list<QString> override;
    auto driverName() const -> QString override;
    auto backup(const QString &fileName) const -> bool override;
};

inline auto SQLite::areForeignKeysActivated() const -> bool {
    return this->foreignKeysActivated;
}

inline auto SQLite::isTest() const -> bool {
    return this->test;
}

inline auto QORM::SQLite::driverName() const -> QString {
    return "QSQLITE";
}

}  // namespace QORM

#endif  // SQLITE_H_
