#ifndef SCHEMA_UPGRADER_H_
#define SCHEMA_UPGRADER_H_

namespace QORM {

class Upgrader {
    const unsigned int version;

 public:
    explicit Upgrader(unsigned int version) : version(version) {}
    Upgrader(const Upgrader&) = delete;
    Upgrader(Upgrader&&) = delete;
    Upgrader& operator=(const Upgrader&) = delete;
    Upgrader& operator=(Upgrader&&) = delete;
    virtual ~Upgrader() {}


};

}  // namespace QORM

#endif  // SCHEMA_UPGRADER_H_
