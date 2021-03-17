#ifndef QORMENTITY_H
#define QORMENTITY_H

#include <algorithm>
#include <set>
#include "./observer.h"
#include "operations/query/condition/condition.h"

namespace QORM {

template<typename Key = int>
class Entity {
    Key key;
    std::set<Observer<Key>*> observers;

 public:
    explicit Entity(const Key &key) : key(key) {}
    Entity(const Entity&) = delete;
    Entity(Entity&&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) = delete;
    virtual ~Entity() {}

    auto getKey() const -> Key { return this->key; }
    void setKey(const Key &key) { this->key = key; }

    auto isAttached(Observer<Key> &observer) const -> bool {
        return observers.find(&observer) != observers.end();
    }

    virtual void attach(Observer<Key> &observer) {
        observers.insert(&observer);
    }

    virtual void detach(Observer<Key> &observer) {
        observers.erase(&observer);
    }

    virtual void notifyChange() const {
        std::for_each(observers.begin(), observers.end(),
            [this](Observer<Key> *observer) {
                observer->onChange(this->key);
            });
    }

    virtual void notifyDelete() const {
        std::for_each(observers.begin(), observers.end(),
            [this](Observer<Key> *observer) {
                observer->onDelete(this->key);
            });
    }

    virtual auto save() -> bool {
        this->notifyChange();
        return true;
    };

    virtual auto erase() -> bool {
        this->notifyDelete();
        return true;
    };

    virtual auto exists() const -> bool = 0;
};

}  // namespace QORM

#endif  // QORMENTITY_H
