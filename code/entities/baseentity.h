#ifndef ENTITIES_BASEENTITY_H_
#define ENTITIES_BASEENTITY_H_

#include <algorithm>
#include <list>
#include <set>
#include <typeindex>
#include "./observer.h"

namespace QORM::Entities {

template<typename Key = int>
class BaseEntity {
    Key key;
    std::set<Observer<Key>*> observers;

 public:
    explicit BaseEntity(const Key &key) : key(key) {}
    BaseEntity(const BaseEntity&) noexcept = delete;
    BaseEntity(BaseEntity&&) noexcept = delete;
    BaseEntity& operator=(const BaseEntity&) = delete;
    BaseEntity& operator=(BaseEntity&&) = delete;
    virtual ~BaseEntity() = default;

    auto getKey() const -> const Key& { return this->key; }
    void setKey(const Key &key) { this->key = key; }

    auto getObservers() const -> const std::set<Observer<Key>*>& {
        return this->observers;
    }

    auto isAttached(Observer<Key> *observer) const {
        return this->observers.find(observer) != this->observers.end();
    }

    auto getTypeIndex() const {
        return std::type_index(typeid(*this));
    }

    virtual void attach(Observer<Key> *observer) {
        if (observer != nullptr) {
            this->observers.insert(observer);
        }
    }

    virtual void detach(Observer<Key> *observer) {
        if (observer != nullptr) {
            this->observers.erase(observer);
        }
    }

    virtual void notifyChange() const {
        std::for_each(this->observers.begin(), this->observers.end(),
            [this](auto *observer) {
                if (observer != nullptr) {
                    observer->onChange(this->key, this->getTypeIndex());
                }
            });
    }

    virtual void notifyDelete() const {
        std::for_each(this->observers.begin(), this->observers.end(),
            [this](auto *observer) {
                if (observer != nullptr) {
                    observer->onDelete(this->key, this->getTypeIndex());
                }
            });
    }
};

}  // namespace QORM::Entities

namespace QORM {

template<class Entity>
using RefList = std::list<std::reference_wrapper<Entity>>;
template<class Entity>
using ConstRefList = std::list<std::reference_wrapper<const Entity>>;

}  // namespace QORM

#endif  // ENTITIES_BASEENTITY_H_
