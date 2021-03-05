#ifndef INTEGER_H
#define INTEGER_H

#include "operations/model/type/type.h"

class Integer : public Type {
 public:
    Integer() : Type("integer") {}
};

#endif  // INTEGER_H
