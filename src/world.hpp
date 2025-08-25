#ifndef MISHA_WORLD_HPP
#define MISHA_WORLD_HPP

#include <any>
#include <typeindex>
#include <unordered_map>

#include "entity.hpp"
#include "sparse_set.hpp"

namespace misha {

class world {
public:
    entity create_entity() noexcept;

    template <typename T>
    void add_component(entity entity, const T& component);

    template <typename T>
    sparse_set<T>& get_components();

private:
    entity m_next_entity = 0;
    std::unordered_map<std::type_index, std::any> m_components;
};

inline entity world::create_entity() noexcept
{
    return m_next_entity++;
}

template <typename T>
void world::add_component(entity entity, const T& component)
{
    sparse_set<T>& components = get_components<T>();
    components.insert(entity, component);
}

template <typename T>
sparse_set<T>& world::get_components()
{
    const auto component_type_idx = std::type_index(typeid(T));
    auto it = m_components.find(component_type_idx);

    if (it == m_components.end()) {
        it = m_components.emplace(component_type_idx, sparse_set<T> {}).first;
    }

    return std::any_cast<sparse_set<T>&>(it->second);
}

}

#endif
