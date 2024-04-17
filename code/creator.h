#ifndef CREATOR_H_
#define CREATOR_H_

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

class Creator {
    std::list<std::reference_wrapper<const Creator>> requiredCreators;

 public:
    explicit Creator(std::list<std::reference_wrapper<const Creator>> = {});
    Creator(const Creator&) = delete;
    Creator(Creator&&) = delete;
    Creator& operator=(const Creator&) = delete;
    Creator& operator=(Creator&&) = delete;
    virtual ~Creator() {}

    auto getRequiredCreators() const ->
        const std::list<std::reference_wrapper<const Creator>>&;
    void addRequiredCreator(const Creator&);
    auto isCreated(const Database&, const std::list<QString> &existingTables,
                   const std::list<QString> &existingViews) const -> bool;
    void createAllAndPopulate(const Database&) const;
    virtual void createTables(const Database&) const = 0;
    virtual void createViews(const Database&) const = 0;
    virtual void populate(const Database&) const = 0;
    virtual auto tables() const -> std::list<QString> = 0;
    virtual auto views() const -> std::list<QString> = 0;

    static void createTable(const Database&, const QString&,
                            const PrimaryKey&, const std::list<Field>& = {},
                            const std::list<ForeignKey>& = {},
                            const std::list<Unique>& = {});
    static void createView(const Database&, const QString&, const Select&);
    static void insert(const Database&, const Insert&);
};

inline auto Creator::getRequiredCreators() const ->
        const std::list<std::reference_wrapper<const Creator>>& {
    return this->requiredCreators;
}

}  // namespace QORM

#endif  // CREATOR_H_
