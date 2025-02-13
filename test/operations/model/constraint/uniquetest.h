#ifndef TEST_OPERATIONS_MODEL_CONSTRAINT_UNIQUETEST_H_
#define TEST_OPERATIONS_MODEL_CONSTRAINT_UNIQUETEST_H_

#include <QTest>

class UniqueTest : public QObject {
    Q_OBJECT

 private slots:
    static void shouldFailWithEmptyName();
    static void shouldFailWithoutFields();
    static void generateShouldSuccessWithoutName();
    static void generateShouldSuccessWithName();
};

#endif  // TEST_OPERATIONS_MODEL_CONSTRAINT_UNIQUETEST_H_
