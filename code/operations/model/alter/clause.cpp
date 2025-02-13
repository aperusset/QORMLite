#include "clause.h"

QORM::Clause::Clause(QString content) :
    content(std::move(content).simplified()) {
    if (this->content.isEmpty()) {
        throw std::invalid_argument("Content must not be empty");
    }
}

auto QORM::Clause::generate() const -> QString {
    return this->content;
}
