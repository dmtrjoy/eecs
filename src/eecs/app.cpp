#include "app.hpp"

#include <utility>

namespace eecs {

app& app::add_system(event event, system system)
{
    m_schedules[std::to_underlying(event)].add_system(system);
    return *this;
}

void app::run()
{
    m_schedules[std::to_underlying(event::startup)].run(m_world);

    // todo: run the update schedule under a while loop tied to the framerate
    // note: this is placeholder logic for now
    const size_t placeholder_iters = 30;

    for (auto i = 0; i < placeholder_iters; ++i) {
        m_schedules[std::to_underlying(event::update)].run(m_world);
    }

    m_schedules[std::to_underlying(event::shutdown)].run(m_world);
}

} // namespace eecs
