#ifndef SCHEMA_OPERATOR_H_
#define SCHEMA_OPERATOR_H_

#include <QString>
#include <list>
#include "operations/model/field.h"
#include "operations/model/constraint/foreignkey.h"
#include "operations/model/constraint/primarykey.h"
#include "operations/model/constraint/unique.h"
#include "operations/query/insert.h"
#include "operations/query/select.h"

namespace QORM {

class Database;

}  // namespace QORM

namespace QORM::Schema {

class Operator {
    bool alreadyExecuted = false;

 public:
    Operator() = default;
    Operator(const Operator&) = delete;
    Operator(Operator&&) = delete;
    Operator& operator=(const Operator&) = delete;
    Operator& operator=(Operator&&) = delete;
    virtual ~Operator() = default;

    virtual inline auto isAlreadyExecuted() const -> bool;
    virtual void setAlreadyExecuted(bool);
    virtual void execute(const Database&) = 0;

    static void createTable(const Database&, const QString&,
                            const PrimaryKey&, const std::list<Field>& = {},
                            const std::list<ForeignKey>& = {},
                            const std::list<Unique>& = {});
    static void createView(const Database&, const QString&, const Select&);
    static void insert(const Database&, const Insert&);
};

auto Operator::isAlreadyExecuted() const -> bool {
    return this->alreadyExecuted;
}

}  // namespace QORM::Schema

#endif  // SCHEMA_OPERATOR_H_
