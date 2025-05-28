#ifndef SCHEMA_UPGRADER_H_
#define SCHEMA_UPGRADER_H_

#include <QMutex>
#include "schema/operator.h"

namespace QORM::Schema {

class Upgrader : public Operator {
    const int version;
    const QString description;

    QMutex upgraderMutex;

 public:
    Upgrader(int version, QString description);
    Upgrader(const Upgrader&) = delete;
    Upgrader(Upgrader&&) = delete;
    Upgrader& operator=(const Upgrader&) = delete;
    Upgrader& operator=(Upgrader&&) = delete;

    inline auto getVersion() const -> int;
    inline auto getDescription() const -> QString;
    void execute(const Database&) override;
    virtual void upgrade(const Database&) const = 0;
};

auto Upgrader::getVersion() const -> int {
    return this->version;
}

auto Upgrader::getDescription() const -> QString {
    return this->description;
}

}  // namespace QORM::Schema

#endif  // SCHEMA_UPGRADER_H_
