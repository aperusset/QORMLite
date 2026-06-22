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
    mutable std::set<Observer<Key>*> observers;

 public:
    explicit BaseEntity(const Key &key) : key(key) {}
    BaseEntity(const BaseEntity&) noexcept = delete;
    BaseEntity(BaseEntity&&) noexcept = delete;
    BaseEntity& operator=(const BaseEntity&) = delete;
    BaseEntity& operator=(BaseEntity&&) = delete;
    ~BaseEntity() = default;

    auto getKey() const noexcept -> const Key { return this->key; }
    void setKey(const Key &key) { this->key = key; }

    auto getTypeIndex() const {
        return std::type_index(typeid(*this));
    }

    auto getObservers() const -> const std::set<Observer<Key>*>& {
        return this->observers;
    }

    auto isAttached(Observer<Key> *observer) const noexcept {
        return this->observers.find(observer) != this->observers.end();
    }

    void attach(Observer<Key> *observer) const {
        if (observer != nullptr) {
            this->observers.insert(observer);
        }
    }

    void detach(Observer<Key> *observer) const {
        if (observer != nullptr) {
            this->observers.erase(observer);
        }
    }

    void notifyChange() const {
        std::for_each(this->observers.begin(), this->observers.end(),
            [this](auto *observer) {
                if (observer != nullptr) {
                    observer->onChange(this->key, this->getTypeIndex());
                }
            });
    }

    void notifyDelete() const {
        std::for_each(this->observers.begin(), this->observers.end(),
            [this](auto *observer) {
                if (observer != nullptr) {
                    observer->onDelete(this->key, this->getTypeIndex());
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
