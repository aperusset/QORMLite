#ifndef QORMOBSERVER_H
#define QORMOBSERVER_H

namespace QORM {

template<typename Key = int>
class Observer {
 public:
    virtual void onChange(const Key&) = 0;
    virtual void onDelete(const Key&) = 0;
    virtual ~Observer() {}
};

}  // namespace QORM

#endif  // QORMOBSERVER_H
