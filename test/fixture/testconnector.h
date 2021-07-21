#ifndef TESTCONNECTOR_H
#define TESTCONNECTOR_H

#include "connectors/connector.h"

class TestConnector : public QORM::Connector {

    static bool preConnectCalled;
    static bool postConnectCalled;
    static bool optimizeCalled;

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
};

#endif // TESTCONNECTOR_H
