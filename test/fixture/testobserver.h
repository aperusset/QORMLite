#ifndef QORMTESTOBSERVER_H
#define QORMTESTOBSERVER_H

#include "observer.h"

class TestObserver : public QORM::Observer<>  {

    static const int INVALID_KEY = -1;

    bool changeNotified;
    bool deleteNotified;
    int changedKey;
    int deletedKey;

public:
    TestObserver();

    void onChange(const int &key) override;
    void onDelete(const int &key) override;

    auto isChangeNotified() const -> bool;
    auto isDeleteNotified() const -> bool;
    auto getChangedKey() const -> int;
    auto getDeletedKey() const -> int;
    void reset();
};

#endif // QORMTESTOBSERVER_H
