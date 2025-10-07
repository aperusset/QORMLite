#ifndef OPERATIONS_QUERY_CTE_H_
#define OPERATIONS_QUERY_CTE_H_

#include <map>
#include <utility>
#include "utils.h"
#include "operations/query.h"
#include "operations/query/select.h"

namespace QORM {

template<class TDQuery = Select>
class CTE : public Query {  // Common Table Expression
    static_assert(std::is_base_of_v<TableQuery, TDQuery>,
                  "TDQuery must extend TableQuery");
    const std::map<QString, Select> withs;
    const TDQuery query;

 public:
    CTE(std::map<QString, Select> withs, TDQuery query) :
            withs(std::move(withs)), query(std::move(query)) {
        if (this->withs.empty()) {
            throw std::invalid_argument("CTE must have at least one with");
        }
        if (std::any_of(this->withs.begin(), this->withs.end(),
                        [](const auto &pair) -> bool {
                            return pair.first.simplified().isEmpty();
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
                return pair.first.simplified() + " as (" +
                       pair.second.generate() + ")";
            })).simplified() + " " + query.generate();
    }

    void bind(QSqlQuery &qSqlQuery) const override {
        Query::bind(qSqlQuery);
        for (const auto &[_, value] : this->withs) {
            value.bind(qSqlQuery);
        }
        this->query.bind(qSqlQuery);
    }
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CTE_H_
