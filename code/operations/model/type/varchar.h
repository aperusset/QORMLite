#ifndef VARCHAR_H
#define VARCHAR_H

#include <QString>
#include "operations/model/type/type.h"

namespace QORM {

class Varchar : public Type {
 public:
    static const int DEFAULT_SIZE = 255;
    static const QString EMPTY;

    // size is just documentation, not a constraint
    explicit Varchar(const int size = DEFAULT_SIZE);
};

}  // namespace QORM

#endif  // VARCHAR_H
