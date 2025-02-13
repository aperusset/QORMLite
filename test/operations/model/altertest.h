#ifndef TEST_OPERATIONS_MODEL_ALTERTEST_H_
#define TEST_OPERATIONS_MODEL_ALTERTEST_H_

#include <QTest>

class AlterTest : public QObject {
    Q_OBJECT

    inline static const QString TABLE_NAME = "table";
    inline static const QString FIELD_NAME = "field";
    inline static const QString RENAMED = "renamed";

 private slots:
    void addColumn();
    void dropColumnShouldFailWithEmptyName();
    void dropColumn();
    void renameColumnToShouldFailWithEmptyFieldName();
    void renameColumnToShouldFailWithEmptyRenamedTo();
    void renameColumnTo();
    void renameToShouldFailWithEmptyRenameTo();
    void renameTo();
    void alterTableShouldFailWithEmptyTableName();
    void alterTable();
};

#endif  // TEST_OPERATIONS_MODEL_ALTERTEST_H_
