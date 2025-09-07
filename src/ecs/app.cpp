#include "app.hpp"

#include <utility>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "window.hpp"

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
    m_world.add_resource<window>("title", width, height);

    m_schedules[std::to_underlying(event::startup)].run(m_world);

    bool done { false };
    SDL_Event event;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
        m_schedules[std::to_underlying(event::update)].run(m_world);
    }

    m_schedules[std::to_underlying(event::shutdown)].run(m_world);

    SDL_Quit();
}

} // namespace eecs
