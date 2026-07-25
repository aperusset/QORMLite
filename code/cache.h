#ifndef CACHE_H_
#define CACHE_H_

#include <QDateTime>
#include <unordered_map>
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
    static_assert(
        std::is_assignable_v<Entity&, const Entity&>,
        "Entity must be assignable for cache refresh");
    using Entry = std::pair<typename Entity::UPtr, QDateTime>;

    const uint32_t ttl;
    std::unordered_map<Key, Entry> entities;

 public:
    inline static constexpr uint32_t DEFAULT_TTL = 7200U;

    explicit Cache(uint32_t ttl = DEFAULT_TTL) : ttl(ttl) {}
    Cache(const Cache&) = delete;
    Cache(Cache&&) = delete;
    Cache& operator=(const Cache&) = delete;
    Cache& operator=(Cache&&) = delete;
    ~Cache() = default;

    auto upsert(const Key &key, typename Entity::UPtr &&entity) -> Entity& {
        if (entity == nullptr) {
            throw std::invalid_argument("Cannot store a null entity");
        }
        const auto expiration = QDateTime::currentDateTime().addSecs(ttl);
        auto [it, inserted] = entities.try_emplace(key, nullptr, expiration);
        if (inserted) {
            it->second.first = std::move(entity);
        } else {
            it->second.second = expiration;
            *it->second.first = std::move(*entity);
        }
        return *it->second.first;
    }

    auto get(const Key &key) const -> Entity& {
        if (this->isValid(key)) {
            return *this->entities.at(key).first.get();
        }
        throw std::out_of_range("Cannot retrieve an entity of type " +
                                std::string(typeid(Entity).name()));
    }

    template<typename Creator>
    auto getOrCreate(const Key &key, Creator&& creator) const -> Entity& {
        return this->isValid(key)
            ? this->get(key)
            : std::forward<Creator>(creator)();
    }

    [[nodiscard]]
    auto contains(const Key &key) const -> bool {
        return entities.find(key) != entities.end();
    }

    [[nodiscard]]
    auto isValid(const Key &key) const -> bool {
        const auto it = entities.find(key);
        return it != entities.end() &&
               it->second.second > QDateTime::currentDateTime();
    }

    void invalidate(const Key &key) {
        if (const auto it = entities.find(key); it != entities.end()) {
            it->second.second = {};
        }
    }

    void invalidateAll() {
        for (auto& [_, value] : entities) {
            value.second = {};
        }
    }

    auto remove(const Key &key) -> bool {
        return static_cast<bool>(entities.erase(key));
    }

    [[nodiscard]]
    auto size() const -> size_t {
        return entities.size();
    }

    void clear() {
        entities.clear();
    }
};

}  // namespace QORM

#endif  // CACHE_H_
