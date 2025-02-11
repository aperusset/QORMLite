#ifndef OPERATIONS_OPERATION_H_
#define OPERATIONS_OPERATION_H_

#include <QString>

namespace QORM {

class Operation {
 public:
    Operation() = default;
    Operation(const Operation&) = default;
    Operation(Operation&&) = default;
    Operation& operator=(const Operation&) = delete;
    Operation& operator=(Operation&&) = delete;
    virtual ~Operation() = default;

    operator QString() const { return this->generate(); }
    virtual auto generate() const -> QString = 0;

    // Prevent heap allocation for database operations
    static void* operator new(size_t) = delete;
    static void* operator new[](size_t) = delete;
};

}  // namespace QORM

#endif  // OPERATIONS_OPERATION_H_
