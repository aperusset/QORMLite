#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <typeindex>

namespace QORM {

template<typename Key = int>
class Observer {
 public:
    virtual void onChange(const Key&, const std::type_index&) = 0;
    virtual void onDelete(const Key&, const std::type_index&) = 0;
    virtual ~Observer() = default;
};

}  // namespace QORM

#endif  // OBSERVER_H_
