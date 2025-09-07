#include "app.hpp"
#include "world.hpp"

#include "gtest/gtest.h"

namespace eecs::test {

namespace {

    void test_system(world& world) { }

} // namespace

// TEST(AppTest, AddSystem)
// {
//     // GIVEN
//     app app;
//
//     // WHEN
//     app.add_system(event::startup, test_system)
//         .add_system(event::update, test_system)
//         .add_system(event::shutdown, test_system)
//         .run();
// }

} // namespace eecs::test
