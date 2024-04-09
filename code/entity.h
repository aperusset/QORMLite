#ifndef ENTITY_H_
#define ENTITY_H_

#include <algorithm>
#include <set>
#include <typeindex>
#include "./observer.h"

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

    auto getObservers() const -> std::set<Observer<Key>*> {
        return observers;
    }

    auto isAttached(Observer<Key> *observer) const -> bool {
        return observers.find(observer) != observers.end();
    }

    auto getTypeIndex() const -> const std::type_index {
        return std::type_index(typeid(*this));
    }

    virtual void attach(Observer<Key> *observer) {
        if (observer != nullptr) {
            observers.insert(observer);
        }
    }

    virtual void detach(Observer<Key> *observer) {
        observers.erase(observer);
    }

    virtual void notifyChange() const {
        std::for_each(observers.begin(), observers.end(),
            [this](Observer<Key> *observer) {
                if (observer != nullptr) {
                    observer->onChange(this->key, getTypeIndex());
                }
            });
    }

    virtual void notifyDelete() const {
        std::for_each(observers.begin(), observers.end(),
            [this](Observer<Key> *observer) {
                if (observer != nullptr) {
                    observer->onDelete(this->key, getTypeIndex());
                }
            });
    }
};

}  // namespace QORM

#endif  // ENTITY_H_
