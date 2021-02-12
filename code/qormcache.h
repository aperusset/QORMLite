#ifndef QORMCACHE_H
#define QORMCACHE_H

#include "qormentity.h"
#include <type_traits>
#include <map>
#include <memory>
#include <functional>

template<typename Key, class Entity>
class QORMCache {

    static_assert(std::is_base_of<QORMEntity<Key>, Entity>::value, "Entity must extend QORMEntity");

    std::map<Key, std::unique_ptr<Entity>> entities;

public:
    auto insert(const Key &key, Entity* const entity) -> Entity& {
        if (entity == nullptr) {
            throw std::string("Cannot store a null entity") + std::string(" with key ") + std::to_string(key);
        }
        if (!this->contains(key)) {
            entities.insert(std::make_pair(key, std::unique_ptr<Entity>(entity)));
        }
        return this->get(key);
    }

    auto contains(const Key &key) const -> bool {
        return entities.count(key);
    }

    auto get(const Key &key) const -> Entity& {
        if (this->contains(key)) {
            return *entities.at(key).get();
        }
        throw std::string("Cannot retrieve an entity of type ") + typeid(this).name() + std::string(" with key ") + std::to_string(key);
    }

    auto getOrCreate(const Key &key, const std::function<Entity&()> &creator) -> Entity& {
        return this->contains(key) ? this->get(key) : creator();
    }

    auto remove(const Key &key) -> bool {
        return entities.erase(key);
    }

    auto size() -> size_t {
        return entities.size();
    }

    void clear() {
        entities.clear();
    }
};

#endif // QORMCACHE_H
