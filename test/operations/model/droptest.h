#ifndef TEST_OPERATIONS_MODEL_DROPTEST_H_
#define TEST_OPERATIONS_MODEL_DROPTEST_H_

#include <QTest>

class DropTest : public QObject {
    Q_OBJECT

    inline static const QString NAME = "name";

 private slots:
    void dropShouldFailIfNameIsBlank();
    void dropTableShouldGenerateExpected();
    void dropViewShouldGenerateExpected();
    void dropTriggerShouldGenerateExpected();
};

#endif  // TEST_OPERATIONS_MODEL_DROPTEST_H_
