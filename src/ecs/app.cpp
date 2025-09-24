#include "app.hpp"

#include <utility>

#include "input.hpp"
#include "window.hpp"

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"

namespace eecs {

app& app::add_system(event event, system system)
{
    m_schedules[std::to_underlying(event)].add_system(system);
    return *this;
}

void app::run()
{
    SDL_Init(SDL_INIT_VIDEO);

    const int width { 800 };
    const int height { 600 };
    m_world.emplace<window>("title", width, height);
    m_world.emplace<input>();
    auto& myinput = m_world.resource<input>();

    m_schedules[std::to_underlying(event::startup)].run(m_world);

    SDL_Event event;
    while (!myinput.quit()) {
        myinput.poll();
        m_schedules[std::to_underlying(event::update)].run(m_world);
    }

    m_schedules[std::to_underlying(event::shutdown)].run(m_world);

    SDL_Quit();
}

} // namespace eecs
