#ifndef INTEGER_H
#define INTEGER_H

#include "operations/model/type/type.h"

namespace QORM {

class Integer : public Type {
 public:
    Integer() : Type("integer") {}
};

}  // namespace QORM

#endif  // INTEGER_H
