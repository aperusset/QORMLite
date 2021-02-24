#ifndef QORMENTITY_H
#define QORMENTITY_H

#include <set>
#include <algorithm>
#include "qormobserver.h"
#include "operations/query/condition.h"

template<typename Key = int>
class QORMEntity {

    Key key;
    std::set<QORMObserver<Key>*> observers;

public:
    explicit QORMEntity(const Key &key) : key(key) {}
    QORMEntity(const QORMEntity&) = delete;
    QORMEntity(QORMEntity&&) = delete;
    QORMEntity& operator=(const QORMEntity&) = delete;
    QORMEntity& operator=(QORMEntity&&) = delete;
    virtual ~QORMEntity() {}

    auto getKey() const -> Key { return this->key; }
    void setKey(const Key &key) { this->key = key; }

    auto isAttached(QORMObserver<Key> &observer) const -> bool {
        return observers.find(&observer) != observers.end();
    }

    virtual void attach(QORMObserver<Key> &observer) {
        observers.insert(&observer);
    }

    virtual void detach(QORMObserver<Key> &observer) {
        observers.erase(&observer);
    }

    virtual void notifyChange() const {
        std::for_each(observers.begin(), observers.end(),
            [this](QORMObserver<Key> *observer) {
                observer->onChange(this->key);
            }
        );
    }

    virtual void notifyDelete() const {
        std::for_each(observers.begin(), observers.end(),
            [this](QORMObserver<Key> *observer) {
                observer->onDelete(this->key);
            }
        );
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

#endif // QORMENTITY_H
