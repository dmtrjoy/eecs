#include "schedule.hpp"

#include "system.hpp"
#include "world.hpp"

namespace eecs {

schedule& schedule::add_system(const system system)
{
    m_systems.emplace_back(system);
    return *this;
}

void schedule::run(world& world) const
{
    for (const system system : m_systems) {
        system(world);
    }
}

} // namespace eecs
