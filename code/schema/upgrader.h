#ifndef SCHEMA_UPGRADER_H_
#define SCHEMA_UPGRADER_H_

namespace QORM {

class Database;

namespace Schema {

class Upgrader {
    const unsigned short version;

 public:
    explicit Upgrader(unsigned int version) : version(version) {}
    Upgrader(const Upgrader&) = delete;
    Upgrader(Upgrader&&) = delete;
    Upgrader& operator=(const Upgrader&) = delete;
    Upgrader& operator=(Upgrader&&) = delete;
    virtual ~Upgrader() {}

    auto getVersion() const -> unsigned short;
    virtual void upgrade(const Database&) const = 0;
};

inline auto Upgrader::getVersion() const -> unsigned short {
    return this->version;
}

}  // namespace Schema

}  // namespace QORM

#endif  // SCHEMA_UPGRADER_H_
