#ifndef QORMOBSERVER_H
#define QORMOBSERVER_H

template<typename Key>
class QORMObserver {

public:
    virtual void onChange(const Key&) = 0;
    virtual void onDelete(const Key&) = 0;
};

#endif // QORMOBSERVER_H
