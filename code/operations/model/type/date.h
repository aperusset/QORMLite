#ifndef DATE_H
#define DATE_H

#include <QString>
#include "operations/model/type/type.h"

class Date : public Type {
 public:
    static const QString NOW;
    Date();
};

#endif  // DATE_H
