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
    QORMEntity& operator=(const QORMEntity&) = delete;
    virtual ~QORMEntity() {}

    auto getKey() const -> Key { return this->key; }
    void setKey(const Key &key) { this->key = key; }

    void notifyChange() const {
        std::for_each(observers.begin(), observers.end(),
            [this](QORMObserver<Key> *observer) {
                observer->onChange(this->key);
            }
        );
    }

    void notifyDelete() const {
        std::for_each(observers.begin(), observers.end(),
            [this](QORMObserver<Key> *observer) {
                observer->onDelete(this->key);
            }
        );
    }

    void attach(QORMObserver<Key> &observer) {
        observers.insert(&observer);
    }

    void detach(QORMObserver<Key> &observer) {
        observers.erase(&observer);
    }

    auto isAttached(QORMObserver<Key> &observer) const -> bool {
        return observers.find(&observer) != observers.end();
    }

    virtual auto exists() const -> bool = 0;
    virtual auto save() -> bool {
        this->notifyChange();
        return true;
    };
    virtual auto erase() -> bool {
        this->notifyDelete();
        return true;
    };
};

#endif // QORMENTITY_H
