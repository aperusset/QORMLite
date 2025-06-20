#ifndef TEST_OPERATIONS_QUERY_ASSIGNMENTTEST_H_
#define TEST_OPERATIONS_QUERY_ASSIGNMENTTEST_H_

#include <QTest>

class AssignmentTest : public QObject {
    Q_OBJECT

    inline static const QString DEFAULT_FIELD_NAME = "defaultFieldName";
    inline static const QVariant DEFAULT_VALUE = QVariant::fromValue(1);

 private slots:
    void emptyOrBlankFieldNameShouldFail();
    void generate();
};

#endif  // TEST_OPERATIONS_QUERY_ASSIGNMENTTEST_H_
