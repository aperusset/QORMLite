#ifndef LIKE_H
#define LIKE_H

#include <QString>
#include <QVariant>
#include "operations/query/condition/condition.h"

namespace QORM {

class Like : public Condition {
 public:
    Like(const QString &field, const QString &likePattern) :
        Condition(" like ", {}, field, "'" + likePattern + "'", QVariant()) {}
};

}  // namespace QORM

#endif  // LIKE_H
