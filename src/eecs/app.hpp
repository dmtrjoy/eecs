#ifndef EECS_APP_HPP
#define EECS_APP_HPP

#include <array>
#include <cstdint>

#include "schedule.hpp"
#include "system.hpp"

namespace eecs {

enum class event : uint8_t {
    startup,
    update,
    shutdown,
    count, // Represents the number of event enums.
};

class app {
public:
    app& add_system(event event, system system);

    void run();

private:
    world m_world;
    std::array<schedule, static_cast<size_t>(event::count)> m_schedules = {};
};

} // namespace eecs

#endif
