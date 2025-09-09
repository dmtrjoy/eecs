#include <print>

#include "app.hpp"
#include "input.hpp"
#include "world.hpp"

namespace {

struct vec2 {
    int x;
    int y;
};

void startup(eecs::world& world) { std::println("startup"); }

void update(eecs::world& world)
{
    auto& input = world.resource<eecs::input>();
    if (input.is_key_pressed(eecs::key::up)) {
        std::println("up key is pressed");
    }
    if (input.is_key_pressed(eecs::key::down)) {
        std::println("down key is pressed");
    }
    if (input.is_key_pressed(eecs::key::left)) {
        std::println("left key is pressed");
    }
    if (input.is_key_pressed(eecs::key::right)) {
        std::println("right key is pressed");
    }
}

void shutdown(eecs::world& world) { std::println("shutdown"); }

} // namespace

int main()
{
    eecs::app app;
    app.add_system(eecs::event::startup, startup)
        .add_system(eecs::event::update, update)
        .add_system(eecs::event::shutdown, shutdown)
        .run();
}
