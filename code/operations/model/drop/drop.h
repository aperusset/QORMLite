#ifndef OPERATIONS_MODEL_DROP_DROP_H_
#define OPERATIONS_MODEL_DROP_DROP_H_

#include "operations/operation.h"

namespace QORM {

enum class DropType {
    Table, View, Trigger
};

class Drop : public Operation {
    const DropType dropType;
    const QString name;

 protected:
    Drop(DropType dropType, QString name);

 public:
    auto getDropType() const -> const DropType&;
    auto getName() const -> const QString&;
    auto generate() const -> QString override;
};

inline auto Drop::getDropType() const -> const DropType& {
    return this->dropType;
}

inline auto Drop::getName() const -> const QString& {
    return this->name;
}

class DropTable : public Drop {
 public:
    explicit DropTable(const QString &name) : Drop(DropType::Table, name) {}
};

class DropView : public Drop {
 public:
    explicit DropView(const QString &name) : Drop(DropType::View, name) {}
};

class DropTrigger : public Drop {
 public:
    explicit DropTrigger(const QString &name) : Drop(DropType::Trigger, name) {}
};

}  // namespace QORM

#endif  // OPERATIONS_MODEL_DROP_DROP_H_
