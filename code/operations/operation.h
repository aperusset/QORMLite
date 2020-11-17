#ifndef OPERATION_H
#define OPERATION_H

#include <QString>

class Operation {

public:
    Operation& operator=(const Operation&) = delete;
    operator QString() const { return this->generate(); }
    virtual ~Operation() {};
    virtual auto generate() const -> QString = 0;
};

#endif // OPERATION_H
