#ifndef EECS_SCHEDULE_HPP
#define EECS_SCHEDULE_HPP

#include <vector>

#include "system.hpp"
#include "world.hpp"

namespace eecs {

class schedule {
public:
    schedule& add_system(system system);

    void run(world& world) const;

private:
    std::vector<system> m_systems;
};

} // namespace eecs

#endif
