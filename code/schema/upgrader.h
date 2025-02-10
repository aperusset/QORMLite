#ifndef SCHEMA_UPGRADER_H_
#define SCHEMA_UPGRADER_H_

#include "schema/operator.h"

namespace QORM::Schema {

class Upgrader : public Operator {
    const unsigned int version;

 public:
    explicit Upgrader(unsigned int version);
    Upgrader(const Upgrader&) = delete;
    Upgrader(Upgrader&&) = delete;
    Upgrader& operator=(const Upgrader&) = delete;
    Upgrader& operator=(Upgrader&&) = delete;
    virtual ~Upgrader() {}

    auto getVersion() const -> unsigned int;
    void execute(const Database&) override;
    virtual void upgrade(const Database&) const = 0;
};

inline auto Upgrader::getVersion() const -> unsigned int {
    return this->version;
}

}  // namespace QORM::Schema

#endif  // SCHEMA_UPGRADER_H_
