#ifndef OPERATIONS_MODEL_TYPE_TYPE_H_
#define OPERATIONS_MODEL_TYPE_TYPE_H_

#include "operations/operation.h"

namespace QORM {

class Type : public Operation {
    const QString name;

 public:
    explicit Type(QString name);
    auto getName() const -> QString;
    auto generate() const -> QString override;
};

inline auto Type::getName() const -> QString {
    return this->name;
}

}  // namespace QORM

#endif  // OPERATIONS_MODEL_TYPE_TYPE_H_
