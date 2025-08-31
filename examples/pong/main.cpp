#include "app.hpp"
#include "world.hpp"

#include <print>

namespace {

struct vec2 {
    int x;
    int y;
};

void startup(eecs::world& world) { std::println("startup"); }

void update(eecs::world& world)
{
    // world.view<vec2>([](vec2& vec) {
    //
    // });
    std::println("update");
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
