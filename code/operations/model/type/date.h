#ifndef DATE_H
#define DATE_H

#include <QString>
#include "operations/model/type/type.h"

namespace QORM {

class Date : public Type {
 public:
    static const QString NOW;
    Date();
};

}  // namespace QORM

#endif  // DATE_H
