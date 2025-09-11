#ifndef CACHE_H_
#define CACHE_H_

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include "entities/baseentity.h"

namespace QORM {

template<typename Key, class Entity>
class Cache {
    static_assert(
        std::is_base_of<Entities::BaseEntity<Key>, Entity>::value,
        "Entity must extend QORM::Entities::BaseEntity<Key>");

    std::map<Key, std::unique_ptr<Entity>> entities;

 public:
    Cache() {}
    Cache(const Cache&) = delete;
    Cache(Cache&&) = delete;
    Cache& operator=(const Cache&) = delete;
    Cache& operator=(Cache&&) = delete;
    virtual ~Cache() = default;

    auto insert(const Key &key, std::unique_ptr<Entity> &&entity) -> Entity& {
        if (entity == nullptr) {
            throw std::invalid_argument("Cannot store a null entity");
        }
        if (!this->contains(key)) {
            entities.insert(std::pair(key,
                std::forward<std::unique_ptr<Entity>>(entity)));
        }
        return this->get(key);
    }

    auto contains(const Key &key) const {
        return static_cast<bool>(entities.count(key));
    }

    auto get(const Key &key) const -> Entity& {
        if (this->contains(key)) {
            return *entities.at(key).get();
        }
        throw std::invalid_argument("Cannot retrieve an entity of type " +
                                    std::string(typeid(this).name()));
    }

    auto getOrCreate(const Key &key,
                     const std::function<Entity&()> &creator) const -> Entity& {
        return this->contains(key) ? this->get(key) : creator();
    }

    auto remove(const Key &key) {
        return static_cast<bool>(entities.erase(key));
    }

    auto size() const -> size_t {
        return entities.size();
    }

    void clear() {
        entities.clear();
    }
};

}  // namespace QORM

#endif  // CACHE_H_
