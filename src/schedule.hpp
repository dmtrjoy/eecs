#ifndef MISHA_SCHEDULE_HPP
#define MISHA_SCHEDULE_HPP

#include <vector>

#include "system.hpp"
#include "world.hpp"

namespace misha {

class schedule {
public:
    schedule& add_system(system system);

    void run(world& world) const;

private:
    std::vector<system> m_systems;
};

} // namespace misha

#endif
