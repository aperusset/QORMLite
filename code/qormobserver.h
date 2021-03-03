#ifndef QORMOBSERVER_H
#define QORMOBSERVER_H

template<typename Key = int>
class QORMObserver {
 public:
    virtual void onChange(const Key&) = 0;
    virtual void onDelete(const Key&) = 0;
    virtual ~QORMObserver() {}
};

#endif  // QORMOBSERVER_H
