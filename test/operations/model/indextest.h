#ifndef TEST_OPERATIONS_MODEL_INDEXTEST_H_
#define TEST_OPERATIONS_MODEL_INDEXTEST_H_

#include <QTest>
#include "operations/model/type/type.h"
#include "operations/model/type/integer.h"

class IndexTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_TABLE_NAME = "defaultTableName";
    inline static const QString DEFAULT_NAME = "defaultName";
    inline static const QString OTHER_NAME = "otherName";
    inline static const QORM::Type DEFAULT_TYPE = QORM::Integer();

 private slots:
    void createEmptyNameShouldFail();
    void createEmptyFieldsShouldFail();
    void createBlankFieldsShouldFail();
    void createGenerateOnSingleField();
    void createGenerateUniqueOnSingleField();
    void createGenerateOnMultipleField();
    void createGenerateUniqueOnMultipleField();
    void dropEmptyNameShouldFail();
    void dropGenerate();
};

#endif  // TEST_OPERATIONS_MODEL_INDEXTEST_H_
