#ifndef QORMTESTOBSERVER_H
#define QORMTESTOBSERVER_H

#include "qormobserver.h"

class QORMTestObserver : public QORMObserver<int>  {

    static const int INVALID_KEY = -1;

    bool changeNotified;
    bool deleteNotified;
    int changedKey;
    int deletedKey;

public:
    QORMTestObserver();

    void onChange(const int &key) override;
    void onDelete(const int &key) override;

    auto isChangeNotified() const -> bool;
    auto isDeleteNotified() const -> bool;
    auto getChangedKey() const -> int;
    auto getDeletedKey() const -> int;
    void reset();
};

#endif // QORMTESTOBSERVER_H
