#ifndef OPERATIONS_QUERY_CONDITION_IN_H_
#define OPERATIONS_QUERY_CONDITION_IN_H_

#include <QString>
#include <set>
#include <utility>
#include <initializer_list>
#include <type_traits>
#include "operations/query/condition/condition.h"
#include "operations/query/select.h"
#include "utils.h"

namespace QORM {

class In : public Condition {
    static auto buildOperator(bool include) -> QString;

    template<typename Container, typename Transformer>
    static auto buildElements(const Container &container,
                              Transformer &&transformer) -> QString {
        return "(" + QORM::Utils::joinToString(container, ", ",
            std::forward<Transformer>(transformer)) + ")";
    }

    template <typename Container>
    static auto transformer() {
        if constexpr (std::is_same_v<typename Container::value_type, int>) {
            return [](const auto &element) { return QString::number(element); };
        } else {
            return [](const auto &element) { return "'" + element + "'"; };
        }
    }

 public:
    explicit In(const QString &field, const Select&, bool include = true);

    template <typename Container,
              typename T = typename Container::value_type,
              typename = std::enable_if_t<std::is_same_v<T, int> ||
                         std::is_same_v<T, QString>>>
    explicit In(const QString &field, const Container &container,
                bool include = true) : Condition(buildOperator(include), {},
            field, buildElements(container, transformer<Container>()),
            QVariant()) {
        if (container.empty()) {
            throw std::invalid_argument("In must contain at least one value.");
        }
    }

    explicit In(const QString &field, std::initializer_list<QString> values,
                bool include = true) :
        In(field, std::set(values.begin(), values.end()), include) {}
    explicit In(const QString &field, std::initializer_list<int> values,
                bool include = true) :
        In(field, std::set(values.begin(), values.end()), include) {}
};

}  // namespace QORM

#endif  // OPERATIONS_QUERY_CONDITION_IN_H_
