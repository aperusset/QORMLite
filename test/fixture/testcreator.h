#ifndef TESTCREATOR_H
#define TESTCREATOR_H

#include "qormcreator.h"

class TestCreator : public QORMCreator {

public:
    explicit TestCreator() {};
    void createTables(const QORMDatabase&) const override;
    void createViews(const QORMDatabase&) const override;
    void populate(const QORMDatabase&) const override;

    static const QString TEST_TABLE;
    static const QString TEST_VIEW;
    static const QString TEST_FIELD;
};

class FakeCreator : public QORMCreator {

public:
    explicit FakeCreator() {};
    void createTables(const QORMDatabase&) const override {}
    void createViews(const QORMDatabase&) const override {}
    void populate(const QORMDatabase&) const override {}
};

#endif // TESTCREATOR_H
