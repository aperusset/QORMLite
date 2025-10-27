#ifndef TEST_OPERATIONS_MODEL_CONSTRAINT_CHECKTEST_H_
#define TEST_OPERATIONS_MODEL_CONSTRAINT_CHECKTEST_H_

#include <QTest>

class CheckTest : public QObject {
    Q_OBJECT

 private slots:
    void shouldFailWithoutConditions();
    void generateShouldSuccessWithoutName();
    void generateShouldSuccessWithName();
};

#endif  // TEST_OPERATIONS_MODEL_CONSTRAINT_CHECKTEST_H_
