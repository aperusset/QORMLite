#ifndef OPERATIONS_QUERY_CTE_H_
#define OPERATIONS_QUERY_CTE_H_

#include <map>
#include "utils.h"
#include "operations/query.h"
#include "operations/query/tabledataquery.h"
#include "operations/query/select.h"

namespace QORM {

template<class TDQuery>
class CTE : public Query {  // Common Table Expression
    static_assert(std::is_base_of<TableQuery, TDQuery>::value,
                  "TDQuery must extend TableDataQuery");
    const std::map<QString, Select> withs;
    const TDQuery query;

 public:
    explicit CTE(std::map<QString, Select> withs, TDQuery query) :
            withs(std::move(withs)), query(std::move(query)) {
        if (this->withs.empty()) {
            throw std::logic_error("CTE must have at least one with");
        }
        if (std::any_of(this->withs.begin(), this->withs.end(),
                        [](const auto &pair) -> bool {
                            return pair.first.isEmpty();
                        })) {
            throw std::invalid_argument("All names must be non-empty");
        }
    }

    auto getWiths() const -> const std::map<QString, Select>& {
        return this->withs;
    }

    auto generate() const -> QString override {
        return ("with " + Utils::joinToString<QString, Select>(this->withs,
            ", ", [](const auto &pair) -> QString {
                return pair.first + " as (" + pair.second.generate() + ")";
            })).simplified() + " " + query.generate();
    }
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CTE_H_
