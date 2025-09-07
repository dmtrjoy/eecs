#ifndef EECS_WINDOW_HPP
#define EECS_WINDOW_HPP

#include <memory>
#include <string>

namespace eecs {

/// A window resource.
class window {
public:
    window(const std::string& title, int width, int height);
    window(const window& other) = delete;
    window(window&& other) noexcept = default;
    window& operator=(const window& other) = delete;
    window& operator=(window&& other) noexcept = default;
    ~window();

    auto operator<=>(const window&) const = default;

private:
    class impl;
    std::unique_ptr<impl> m_pimpl;
};

} // namespace eecs

#endif // !EECS_WINDOW_HPP
