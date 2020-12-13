#ifndef VIEWTEST_H
#define VIEWTEST_H

#include <QtTest/QtTest>

class ViewTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_VIEW_NAME;
    static const QString DEFAULT_TABLE_NAME;
    static const QString DEFAULT_FIELD_NAME;

private slots:
    static void selectWithBindableShouldFail();
    static void generate();
};

#endif // VIEWTEST_H
