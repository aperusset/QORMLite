#ifndef OPERATION_H
#define OPERATION_H

#include <QString>

class Operation {
 public:
    Operation() = default;
    Operation(const Operation&) = default;
    Operation(Operation&&) = default;
    Operation& operator=(const Operation&) = delete;
    Operation& operator=(Operation&&) = delete;
    virtual ~Operation() {}

    operator QString() const { return this->generate(); }
    virtual auto generate() const -> QString = 0;

    // Prevent heap allocation for database operations
    static void* operator new(size_t) = delete;
    static void* operator new[](size_t) = delete;
};

#endif  // OPERATION_H
