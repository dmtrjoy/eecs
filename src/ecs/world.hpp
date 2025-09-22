#ifndef EECS_WORLD_HPP
#define EECS_WORLD_HPP

#include <stdexcept>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "any.hpp"
#include "entity.hpp"
#include "sparse_set.hpp"

namespace eecs {

/// A specialized container for storing, querying, and interacting with
/// entities, components, and resources.
class world {
public:
    /// Creates a new `::entity`.
    ///
    /// \return A new `::entity` identifier.
    entity create() noexcept { return m_next_entity++; }

    /// Adds a component to an ::entity.
    ///
    /// \tparam Component The type of component to add.
    /// \param entity The ::entity to add the component to.
    /// \param component The component to add.
    template <typename Component>
    void insert(entity entity, const Component& component)
    {
        sparse_set<Component>& components { this->components<Component>() };
        components.insert(entity, component);
    }

    /// Adds a resource to this ::world. The resource is constructed in place.
    ///
    /// Resources are unique data types managed by the ::world. They are
    /// similar to singletons in that only one instance can exist at any time;
    /// however, resources do not have global state. Their lifetimes are tied
    /// to the ::world that owns them.
    ///
    /// \tparam Resource The type of resource to add.
    /// \tparam Args Parameter pack for constructor argument types.
    /// \param args Arguments forwarded to the resource constructor.
    template <typename Resource, typename... Args>
    void add_resource(Args&&... args);

    /// Clears all entities from this ::world.
    void clear_entities();

    /// Retrieves this ::world's component collection of the given type.
    ///
    /// \tparam Component The type of component collection to retrieve.
    /// \return A reference to the component collection.
    template <typename Component>
    sparse_set<Component>& components();

    /// Retrives a resource from this ::world.
    ///
    /// \tparam Resource The type of resource to retrieve.
    /// \return A reference to the resource.
    /// \throws std::out_of_range if the resource is not found.
    template <typename Resource>
    Resource& resource();

    /// Calls a function on each ::entity with the given types of components.
    ///
    /// \tparam Components The types of components that the entities must have.
    /// \tparam Fn The type of function to call.
    /// \param fn The function to call for each matching ::entity.
    template <typename... Components, typename Fn>
    void view(Fn&& fn);

private:
    entity m_next_entity = 0;
    std::unordered_map<std::type_index, any> m_components;
    std::unordered_map<std::type_index, any> m_resources;
};

template <typename Resource, typename... Args>
void world::add_resource(Args&&... args)
{
    const auto type_id { std::type_index(typeid(Resource)) };
    m_resources.emplace(std::piecewise_construct,
        std::forward_as_tuple(type_id),
        std::forward_as_tuple(
            std::in_place_type_t<Resource> {}, std::forward<Args>(args)...));
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
        it = m_components
                 .emplace(std::piecewise_construct,
                     std::forward_as_tuple(type_id),
                     std::forward_as_tuple(
                         std::in_place_type_t<sparse_set<Component>> {}))
                 .first;
    }

    return any_cast<sparse_set<Component>>(it->second);
}

template <typename Resource>
Resource& world::resource()
{
    const auto type_id { std::type_index(typeid(Resource)) };
    const auto it { m_resources.find(type_id) };

    if (it == m_resources.end()) {
        throw std::out_of_range("Resource not found");
    }

    return any_cast<Resource>(it->second);
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
