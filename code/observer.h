#ifndef OBSERVER_H_
#define OBSERVER_H_

namespace QORM {

template<typename Entity>
class Observer {
 public:
    virtual void onChange(const Entity&) = 0;
    virtual void onDelete(const Entity&) = 0;
    virtual ~Observer() = default;
};

}  // namespace QORM

#endif  // OBSERVER_H_
