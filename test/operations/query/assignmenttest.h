#ifndef ASSIGNEMENTTEST_H
#define ASSIGNEMENTTEST_H

#include <QtTest/QtTest>

class AssignmentTest : public QObject {

    Q_OBJECT

    static const QString DEFAULT_FIELD_NAME;
    static const QVariant DEFAULT_VALUE;

private slots:
    static void generate();
};

#endif // ASSIGNEMENTTEST_H
