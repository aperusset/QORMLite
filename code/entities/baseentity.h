#ifndef ENTITIES_BASEENTITY_H_
#define ENTITIES_BASEENTITY_H_

#include <algorithm>
#include <list>
#include <memory>
#include <set>
#include <vector>
#include "./observer.h"

namespace QORM::Entities {

template<typename Derived, typename Key = int>
class BaseEntity {
    Key key;
    mutable std::set<Observer<Derived>*> observers;

 public:
    explicit BaseEntity(const Key &key) : key(key) {}
    BaseEntity(const BaseEntity&) noexcept = delete;
    BaseEntity(BaseEntity&&) noexcept = delete;
    BaseEntity& operator=(const BaseEntity&) = delete;
    BaseEntity& operator=(BaseEntity&&) = delete;
    ~BaseEntity() = default;

    auto getKey() const noexcept -> const Key { return this->key; }
    void setKey(const Key &key) { this->key = key; }

    auto getObservers() const -> const std::set<Observer<Derived>*>& {
        return this->observers;
    }

    auto isAttached(const Observer<Derived> &observer) const noexcept {
        return this->observers.find(const_cast<Observer<Derived>*>(
            std::addressof(observer))) != this->observers.end();
    }

    void attach(Observer<Derived> *observer) const {
        if (observer != nullptr) {
            this->observers.insert(observer);
        }
    }

    void detach(Observer<Derived> *observer) const {
        this->observers.erase(observer);
    }

    void notifyChange() const {
        std::for_each(this->observers.begin(), this->observers.end(),
            [this](auto *observer) {
                if (observer != nullptr) {
                    observer->onChange(static_cast<const Derived&>(*this));
                }
            });
    }

    void notifyDelete() const {
        std::for_each(this->observers.begin(), this->observers.end(),
            [this](auto *observer) {
                if (observer != nullptr) {
                    observer->onDelete(static_cast<const Derived&>(*this));
                }
            });
    }

    using KeyType = Key;

    using Ref = std::reference_wrapper<Derived>;
    using ConstRef = std::reference_wrapper<const Derived>;
    using UPtr = std::unique_ptr<Derived>;
    using SPtr = std::shared_ptr<Derived>;

    using RefList = std::list<Ref>;
    using ConstRefList = std::list<ConstRef>;
    using RefVector = std::vector<Ref>;
    using ConstRefVector = std::vector<ConstRef>;
};

}  // namespace QORM::Entities

#endif  // ENTITIES_BASEENTITY_H_
