#ifndef CACHE_H_
#define CACHE_H_

#include <QDateTime>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <utility>
#include "entities/baseentity.h"

namespace QORM {

template<typename Entity>
class Cache {
    using Key = typename Entity::KeyType;
    static_assert(
        std::is_base_of_v<Entities::BaseEntity<Entity, Key>, Entity>,
        "Entity must extend QORM::Entities::BaseEntity<Entity, Key>");

    const uint32_t ttl;
    std::map<Key, std::pair<std::unique_ptr<Entity>, QDateTime>> entities;

 public:
    inline static const uint32_t DEFAULT_TTL = 7200U;

    explicit Cache(uint32_t ttl = DEFAULT_TTL) : ttl(ttl) {}
    Cache(const Cache&) = delete;
    Cache(Cache&&) = delete;
    Cache& operator=(const Cache&) = delete;
    Cache& operator=(Cache&&) = delete;
    virtual ~Cache() = default;

    auto insert(const Key &key, std::unique_ptr<Entity> &&entity) -> Entity& {
        if (entity == nullptr) {
            throw std::invalid_argument("Cannot store a null entity");
        }
        const auto expiration = QDateTime::currentDateTime().addSecs(ttl);
        return *entities.try_emplace(key, std::pair(std::move(entity),
                      std::move(expiration))).first->second.first;
    }

    auto get(const Key &key) const -> Entity& {
        if (this->isValid(key)) {
            return *this->entities.at(key).first.get();
        }
        throw std::invalid_argument("Cannot retrieve an entity of type " +
                                    std::string(typeid(Entity).name()));
    }

    auto getOrCreate(const Key &key,
                     const std::function<Entity&()> &creator) const -> Entity& {
        return this->isValid(key) ? this->get(key) : creator();
    }

    auto contains(const Key &key) const {
        return static_cast<bool>(entities.count(key));
    }

    auto isValid(const Key &key) const {
        return this->contains(key) &&
               this->entities.at(key).second > QDateTime::currentDateTime();
    }

    auto invalidate(const Key &key) {
        if (this->contains(key)) {
            this->entities.at(key).second = QDateTime();
        }
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
