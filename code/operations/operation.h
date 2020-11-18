#ifndef OPERATION_H
#define OPERATION_H

#include <QString>

class Operation {

public:
    operator QString() const { return this->generate(); }
    virtual auto generate() const -> QString = 0;

    Operation& operator=(const Operation&) = delete;

    // Prevent heap allocation for database operations
    // https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Requiring_or_Prohibiting_Heap-based_Objects
    static void* operator new(size_t) = delete;
    static void* operator new[](size_t) = delete;
};

#endif // OPERATION_H
