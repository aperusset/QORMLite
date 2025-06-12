#ifndef OPERATIONS_QUERY_WITH_H_
#define OPERATIONS_QUERY_WITH_H_

#include <map>
#include "operations/operation.h"
#include "operations/query/select.h"

namespace QORM {

class With : public Operation {
    const std::map<QString, Select> selects;

 public:
    explicit With(std::map<QString, Select>);
    auto getSelects() const -> const std::map<QString, Select>&;
    auto generate() const -> QString override;
};

inline auto With::getSelects() const -> const std::map<QString, Select>& {
    return this->selects;
}

}  // namespace QORM

#endif  // OPERATIONS_QUERY_WITH_H_
