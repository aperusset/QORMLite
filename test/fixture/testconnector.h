#ifndef TEST_FIXTURE_TESTCONNECTOR_H_
#define TEST_FIXTURE_TESTCONNECTOR_H_

#include "connectors/connector.h"

class TestConnector : public QORM::Connector {
    inline static bool preConnectCalled = false;
    inline static bool postConnectCalled = false;
    inline static bool optimizeCalled = false;

 public:
    explicit TestConnector(const QString &name) : Connector(name) {}

    void preConnect() const override {
        QORM::Connector::preConnect();
        preConnectCalled = true;
    }

    void postConnect() const override {
        QORM::Connector::postConnect();
        postConnectCalled = true;
    }

    void optimize() const override {
        optimizeCalled = true;
    }

    auto driverName() const -> QString override {
        return "QSQLITE";
    }

    auto databaseName() const -> QString override {
        return this->getName();
    }

    auto backup(const QString&) const -> bool override {
        return false;
    }

    auto isPreConnectCalled() const -> bool {
        return preConnectCalled;
    }

    auto isPostConnectCalled() const -> bool {
        return postConnectCalled;
    }

    auto isOptimizeCalled() const -> bool {
        return optimizeCalled;
    }

    static void reset() {
        preConnectCalled = false;
        postConnectCalled = false;
        optimizeCalled = false;
    }
};

#endif  // TEST_FIXTURE_TESTCONNECTOR_H_
