#include "window.hpp"

#include <memory>
#include <string>

#include "SDL3/SDL_video.h"

namespace eecs {

class window::impl {
public:
    impl(const std::string& title, const int width, const int height)
        : m_window(SDL_CreateWindow(
              title.c_str(), width, height, SDL_WINDOW_RESIZABLE))
    {
    }

    ~impl()
    {
        if (m_window != nullptr) {
            SDL_DestroyWindow(m_window);
        }
    }

private:
    SDL_Window* m_window { nullptr };
};

window::window(const std::string& title, const int width, const int height)
    : m_pimpl(std::make_unique<impl>(title, width, height))
{
}

window::~window() = default;

} // namespace eecs
