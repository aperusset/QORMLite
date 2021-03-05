#ifndef LIKE_H
#define LIKE_H

#include <QString>
#include <QVariant>
#include "operations/query/condition/condition.h"

class Like : public Condition {
 public:
    Like(const QString &field, const QString &likePattern) :
        Condition(" like ", {}, field, "'" + likePattern + "'", QVariant()) {}
};

#endif  // LIKE_H
