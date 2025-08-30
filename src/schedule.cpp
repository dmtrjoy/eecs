#include "schedule.hpp"

#include "system.hpp"
#include "world.hpp"

namespace misha {

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

} // namespace misha
