#ifndef EECS_WORLD_HPP
#define EECS_WORLD_HPP

#include <any>
#include <stdexcept>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "entity.hpp"
#include "sparse_set.hpp"

namespace eecs {

/// A specialized container for storing, querying, and operating on entities,
/// components, and resources.
class world {
public:
    /// Creates a new entity.
    entity create_entity() noexcept;

    /// Adds a component to an entity.
    template <typename Component>
    void add_component(entity entity, const Component& component);

    /// Adds a resource.
    template <typename Resource, typename... Args>
    void add_resource(Args&&... args);

    /// Clears all entities.
    void clear_entities();

    /// Retrieves this world's components collection of a given type.
    template <typename Component>
    sparse_set<Component>& components();

    /// Retrives a resource.
    template <typename Resource>
    Resource& resource();

    /// Calls a function on each entity with the given types of components.
    template <typename... Components, typename Fn>
    void view(Fn&& fn);

private:
    entity m_next_entity = 0;
    std::unordered_map<std::type_index, std::any> m_components;
    std::unordered_map<std::type_index, std::any> m_resources;
};

inline entity world::create_entity() noexcept { return m_next_entity++; }

template <typename Component>
void world::add_component(entity entity, const Component& component)
{
    sparse_set<Component>& components { this->components<Component>() };
    components.insert(entity, component);
}

template <typename Resource, typename... Args>
void world::add_resource(Args&&... args)
{
    const auto type_id { std::type_index(typeid(Resource)) };
    m_resources[type_id] = Resource { std::forward<Args>(args)... };
}

inline void world::clear_entities()
{
    m_next_entity = 0;
    m_components.clear();
}

template <typename Component>
sparse_set<Component>& world::components()
{
    const auto type_id { std::type_index(typeid(Component)) };
    auto it { m_components.find(type_id) };

    if (it == m_components.end()) {
        it = m_components.emplace(type_id, sparse_set<Component> {}).first;
    }

    return std::any_cast<sparse_set<Component>&>(it->second);
}

template <typename Resource>
Resource& world::resource()
{
    const auto type_id { std::type_index(typeid(Resource)) };
    const auto it { m_resources.find(type_id) };

    if (it == m_resources.end()) {
        throw std::out_of_range("Resource not found");
    }

    return std::any_cast<Resource&>(it->second);
}

template <typename... Components, typename Fn>
void world::view(Fn&& fn)
{
    auto& first_components {
        components<std::tuple_element_t<0, std::tuple<Components...>>>()
    };
    for (const auto& [entity, _] : first_components) {
        if ((components<Components>().contains(entity) && ...)) {
            std::forward<Fn>(fn)(entity, components<Components>()[entity]...);
        }
    }
}

} // namespace eecs

#endif
