#ifndef TEST_OPERATIONS_MODEL_CONSTRAINT_UNIQUETEST_H_
#define TEST_OPERATIONS_MODEL_CONSTRAINT_UNIQUETEST_H_

#include <QTest>

class UniqueTest : public QObject {
    Q_OBJECT

 private slots:
    void shouldFailWithoutFields();
    void generateShouldSuccessWithoutName();
    void generateShouldSuccessWithName();
};

#endif  // TEST_OPERATIONS_MODEL_CONSTRAINT_UNIQUETEST_H_
