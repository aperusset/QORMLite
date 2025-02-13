#ifndef TEST_OPERATIONS_MODEL_CONSTRAINT_FOREIGNKEYTEST_H_
#define TEST_OPERATIONS_MODEL_CONSTRAINT_FOREIGNKEYTEST_H_

#include <QTest>

class ForeignKeyTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_TARGET_TABLE = "targetTable";

 private slots:
    static void emptyReferencesListShouldFail();
    static void generateCascade();
    static void generateRestrict();
    static void generateSetNull();
    static void generateSetDefault();
    static void generateMultipleFields();
};

#endif  // TEST_OPERATIONS_MODEL_CONSTRAINT_FOREIGNKEYTEST_H_
