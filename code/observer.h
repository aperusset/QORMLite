#ifndef OBSERVER_H_
#define OBSERVER_H_

namespace QORM {

template<typename Key = int>
class Observer {
 public:
    virtual void onChange(const Key&) = 0;
    virtual void onDelete(const Key&) = 0;
    virtual ~Observer() {}
};

}  // namespace QORM

#endif  // OBSERVER_H_
