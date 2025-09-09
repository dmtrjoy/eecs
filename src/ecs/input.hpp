#ifndef EECS_INPUT_HPP
#define EECS_INPUT_HPP

#include <cstdint>
#include <memory>

namespace eecs {

enum class key : uint8_t {
    left,
    right,
    up,
    down,
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n
};

class input {
public:
    input();
    ~input();

    void add_action();
    [[nodiscard]] bool is_key_pressed(key key);
    void poll();
    [[nodiscard]] bool quit() const;

private:
    class impl;
    std::unique_ptr<impl> m_pimpl;
};

} // namespace eecs

#endif
