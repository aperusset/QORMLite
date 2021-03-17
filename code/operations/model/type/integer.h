#ifndef OPERATIONS_MODEL_TYPE_INTEGER_H_
#define OPERATIONS_MODEL_TYPE_INTEGER_H_

#include "operations/model/type/type.h"

namespace QORM {

class Integer : public Type {
 public:
    Integer() : Type("integer") {}
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_TYPE_INTEGER_H_
