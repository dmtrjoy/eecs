#include "input.hpp"

#include <memory>
#include <print>
#include <unordered_map>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"

namespace eecs {

class input::impl {
public:
    [[nodiscard]] bool is_key_pressed(const key key)
    {
        if (key == key::up && m_pressed[SDLK_UP]) {
            return true;
        }
        if (key == key::down && m_pressed[SDLK_DOWN]) {
            return true;
        }
        if (key == key::left && m_pressed[SDLK_LEFT]) {
            return true;
        }
        if (key == key::right && m_pressed[SDLK_RIGHT]) {
            return true;
        }
        return false;
    }

    void poll()
    {
        m_just_pressed.clear();
        m_just_released.clear();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                m_quit = true;
            }

            if (event.type == SDL_EVENT_KEY_DOWN) {
                m_pressed[event.key.key] = true;
                if (!event.key.repeat) {
                    m_just_pressed[event.key.key] = true;
                }
            }

            if (event.type == SDL_EVENT_KEY_UP) {
                m_pressed[event.key.key] = false;
                m_just_released[event.key.key] = true;
            }
        }
    }

    [[nodiscard]] bool quit() const { return m_quit; }

private:
    std::unordered_map<SDL_Keycode, bool> m_pressed;
    std::unordered_map<SDL_Keycode, bool> m_just_pressed;
    std::unordered_map<SDL_Keycode, bool> m_just_released;
    bool m_quit { false };
};

input::input()
    : m_pimpl(std::make_unique<impl>())
{
}

input::~input() = default;

bool input::is_key_pressed(const key key)
{
    return m_pimpl->is_key_pressed(key);
}

void input::poll() { m_pimpl->poll(); }

bool input::quit() const { return m_pimpl->quit(); }

} // namespace eecs
