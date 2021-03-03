#ifndef QORMCREATOR_H
#define QORMCREATOR_H

#include <QString>
#include <list>
#include "operations/model/primarykey.h"
#include "operations/model/foreignkey.h"
#include "operations/model/field.h"
#include "operations/query/select.h"
#include "operations/query/insert.h"

class QORMDatabase;

class QORMCreator {

public:
    void createAllAndPopulate(const QORMDatabase&) const;
    virtual void createTables(const QORMDatabase&) const = 0;
    virtual void createViews(const QORMDatabase&) const = 0;
    virtual void populate(const QORMDatabase&) const = 0;

    QORMCreator() {}
    QORMCreator(const QORMCreator&) = delete;
    QORMCreator& operator=(const QORMCreator&) = delete;
    virtual ~QORMCreator() {}

    static void createTable(const QORMDatabase&, const QString&, const PrimaryKey&, const std::list<Field>& = {}, const std::list<ForeignKey>& = {});
    static void createView(const QORMDatabase&, const QString&, const Select&);
    static void insert(const QORMDatabase&, const Insert&);
};

#endif // QORMCREATOR_H
