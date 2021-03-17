#ifndef QORMCACHE_H
#define QORMCACHE_H

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include "./entity.h"

namespace QORM {

template<typename Key, class Entity>
class Cache {
    static_assert(
        std::is_base_of<QORM::Entity<Key>, Entity>::value,
        "Entity must extend QORM::Entity");

    std::map<Key, std::unique_ptr<Entity>> entities;

 public:
    auto insert(Key key, std::unique_ptr<Entity> &&entity) -> Entity& {
        if (entity == nullptr) {
            throw std::string("Cannot store a null entity with key ")
                    .append(std::to_string(key));
        }
        if (!this->contains(key)) {
            entities.insert(std::make_pair(
                std::move(key),
                std::forward<std::unique_ptr<Entity>>(entity)));
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
        throw std::string("Cannot retrieve an entity of type ")
                .append(typeid(this).name())
                .append(" with key ")
                .append(std::to_string(key));
    }

    auto getOrCreate(const Key &key,
                     const std::function<Entity&()> &creator) -> Entity& {
        return this->contains(key) ? this->get(key) : creator();
    }

    auto remove(const Key &key) -> bool {
        return entities.erase(key);
    }

    auto size() const -> size_t {
        return entities.size();
    }

    void clear() {
        entities.clear();
    }
};

}  // namespace QORM

#endif  // QORMCACHE_H
