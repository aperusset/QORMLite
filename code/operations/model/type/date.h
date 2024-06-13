#ifndef OPERATIONS_MODEL_TYPE_DATE_H_
#define OPERATIONS_MODEL_TYPE_DATE_H_

#include <QString>
#include "operations/model/type/type.h"

namespace QORM {

class Date : public Type {
 public:
    inline static const QString NOW = "date('now')";
    Date();
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_TYPE_DATE_H_
