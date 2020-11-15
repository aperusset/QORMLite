#ifndef OPERATION_H
#define OPERATION_H

#include <QString>

class Operation {

public:
    virtual ~Operation() {};
    virtual auto generate() const -> QString = 0;
};

#endif // OPERATION_H
