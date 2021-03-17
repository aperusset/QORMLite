#ifndef UPPER_H
#define UPPER_H

#include <QString>
#include "operations/query/selection/selection.h"

namespace QORM {

class Upper : public Selection {
 public:
    explicit Upper(const QString &fieldToUpper) :
        Selection("upper(" +  fieldToUpper + ")", QString()) {}
};

}  // namespace QORM

#endif  // UPPER_H
