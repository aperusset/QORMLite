#ifndef VARCHAR_H
#define VARCHAR_H

#include <QString>
#include "operations/model/type/type.h"

class Varchar : public Type {
 public:
    static const int DEFAULT_SIZE = 255;
    static const QString EMPTY;

    // size is just documentation, not a constraint
    explicit Varchar(const int size = DEFAULT_SIZE);
};

#endif  // VARCHAR_H
