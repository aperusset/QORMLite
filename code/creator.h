#ifndef CREATOR_H_
#define CREATOR_H_

#include <QString>
#include <list>
#include "operations/model/field.h"
#include "operations/model/foreignkey.h"
#include "operations/model/primarykey.h"
#include "operations/query/insert.h"
#include "operations/query/select.h"

namespace QORM {

class Database;

class Creator {
 public:
    Creator() {}
    Creator(const Creator&) = delete;
    Creator(Creator&&) = delete;
    Creator& operator=(const Creator&) = delete;
    Creator& operator=(Creator&&) = delete;
    virtual ~Creator() {}

    void createAllAndPopulate(const Database&) const;
    virtual void createTables(const Database&) const = 0;
    virtual void createViews(const Database&) const = 0;
    virtual void populate(const Database&) const = 0;

    static void createTable(const Database&, const QString&,
                            const PrimaryKey&, const std::list<Field>& = {},
                            const std::list<ForeignKey>& = {});
    static void createView(const Database&, const QString&, const Select&);
    static void insert(const Database&, const Insert&);
};

}  // namespace QORM

#endif  // CREATOR_H_
