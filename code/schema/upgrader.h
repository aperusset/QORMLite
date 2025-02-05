#ifndef SCHEMA_UPGRADER_H_
#define SCHEMA_UPGRADER_H_

namespace QORM {

class Database;

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
    void upgrade(const Database&) const {}
};

inline auto Upgrader::getVersion() const -> unsigned short {
    return this->version;
}

}  // namespace QORM

#endif  // SCHEMA_UPGRADER_H_
