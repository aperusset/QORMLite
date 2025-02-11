#ifndef TEST_REPOSITORIES_SCHEMAVERSIONREPOSITORYTEST_H_
#define TEST_REPOSITORIES_SCHEMAVERSIONREPOSITORYTEST_H_

#include "fixture/maindatabasetest.h"

class SchemaVersionRepositoryTest : public MainDatabaseTest {
    Q_OBJECT

 public:
    auto databaseName() const -> QString override {
        return "schemaversionrepositorytest";
    }

 private slots:
    void tableName();
    void keyCondition();
    void fields();
    void saveAndGet();
    void newSchemaVersionShouldFail();
    void getCurrentSchemaVersionShouldFail();
    void getCurrentSchemaVersionShouldReturnInitial();
    void getCurrentSchemaVersionShouldReturnLatest();

    void init() {
        this->deleteAllDatabases();
    }

    void cleanup() {
        this->deleteAllDatabases();
    }
};

#endif  // TEST_REPOSITORIES_SCHEMAVERSIONREPOSITORYTEST_H_
