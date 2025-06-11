#include "with.h"
#include "./utils.h"

QORM::With::With(std::map<QString, Select> selects) :
    selects(std::move(selects)) {
    if (this->selects.empty()) {
        throw std::invalid_argument("With must have at least one select");
    }
    if (std::any_of(this->selects.begin(), this->selects.end(),
                    [](const auto &pair) { return pair.first.isEmpty(); })) {
        throw std::invalid_argument("All selects must have a non-empty name");
    }
}

auto QORM::With::generate() const -> QString {
    return ("with " + Utils::joinToString<QString, Select>(this->selects,
        QString(", "), [](const auto &pair) -> QString {
            return pair.first + " as (" + pair.second.generate() + ")";
        })).simplified();
}
