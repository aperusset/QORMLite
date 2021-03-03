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
    // https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Requiring_or_Prohibiting_Heap-based_Objects
    static void* operator new(size_t) = delete;
    static void* operator new[](size_t) = delete;
};

#endif  // OPERATION_H
