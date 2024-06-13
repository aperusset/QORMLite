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

}  // namespace QORM

#endif  // ENTITY_H_
