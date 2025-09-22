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

    /// Inserts a component into this `::world` and associates it with an
    /// `::entity`.
    ///
    /// \tparam T The type of component to insert.
    /// \param entity The `::entity` to associate the component with.
    /// \param component The component to insert.
    template <typename T>
    void insert(entity entity, const T& component)
    {
        sparse_set<T>& components { this->components<T>() };
        components.insert(entity, component);
    }

    /// Inserts a new component into this `::world` constructed in-place with
    /// the given `args` and associates it with an `::entity`.
    ///
    /// \tparam T The type of component to insert.
    /// \tparam Args The pack of component constructor parameter types.
    /// \param entity The `::entity` to associate the component with.
    /// \param args The arguments to forward to the constructor of the
    ///     component.
    template <typename T, typename... Args>
    void emplace(const entity entity, Args&&... args)
    {
        sparse_set<T>& components { this->components<T>() };
        components.emplace(entity, std::forward<Args>(args)...);
    }

    /// Inserts a new resource into this `::world` constructed in-place with
    /// the given `args`.
    ///
    /// Resources are unique data types managed by the `::world`. They are
    /// similar to singletons in that only one instance can exist at any time;
    /// however, resources do not have global state. Their lifetimes are tied
    /// to the `::world` that owns them.
    ///
    /// \tparam T The type of resource to insert.
    /// \tparam Args The pack of resource constructor parameter types.
    /// \param args The arguments to forward to the constructor of the
    ///     resource.
    template <typename T, typename... Args>
    void emplace(Args&&... args)
    {
        const auto type_id { std::type_index(typeid(T)) };
        m_resources.emplace(std::piecewise_construct,
            std::forward_as_tuple(type_id),
            std::forward_as_tuple(
                std::in_place_type_t<T> {}, std::forward<Args>(args)...));
    }

    /// Clears all entities from this `::world`.
    void clear()
    {
        m_next_entity = 0;
        m_components.clear();
    }

    /// Returns this `::world`'s component collection of the given type.
    ///
    /// \tparam T The type of component collection to return.
    /// \return A reference to the component collection.
    template <typename T>
    sparse_set<T>& components()
    {
        const auto type_id { std::type_index(typeid(T)) };
        auto it { m_components.find(type_id) };

        if (it == m_components.end()) {
            it = m_components
                     .emplace(std::piecewise_construct,
                         std::forward_as_tuple(type_id),
                         std::forward_as_tuple(
                             std::in_place_type_t<sparse_set<T>> {}))
                    .first;
        }

        return any_cast<sparse_set<T>>(it->second);
    }

    /// Returns a resource from this `::world`.
    ///
    /// \tparam T The type of resource to return.
    /// \return A reference to the resource.
    /// \throws std::out_of_range if the resource is not found.
    template <typename T>
    T& resource()
    {
        const auto type_id { std::type_index(typeid(T)) };
        const auto it { m_resources.find(type_id) };

        if (it == m_resources.end()) {
            throw std::out_of_range("Resource not found");
        }

        return any_cast<T>(it->second);
    }

    /// Invokes a function on each `::entity` associated with the given types
    /// of components.
    ///
    /// \tparam T The types of components that each `::entity` must be
    ///     associated with.
    /// \tparam Fn The type of function to invoke.
    /// \param fn The function to invoke for each matching `::entity`.
    template <typename... T, typename Fn>
    void view(Fn&& fn)
    {
        auto& first_components {
            components<std::tuple_element_t<0, std::tuple<T...>>>()
        };
        for (const auto& [entity, _] : first_components) {
            if ((components<T>().contains(entity) && ...)) {
                std::forward<Fn>(fn)(entity, components<T>()[entity]...);
            }
        }
    }

private:
    entity m_next_entity = 0;
    std::unordered_map<std::type_index, any> m_components;
    std::unordered_map<std::type_index, any> m_resources;
};

} // namespace eecs

#endif
