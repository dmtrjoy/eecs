#include "schedule.hpp"

#include "entity.hpp"
#include "world.hpp"

#include "gtest/gtest.h"

namespace eecs::test {

namespace {

    struct test_component {
        bool has_run = false;
    };

    void create(world& world)
    {
        entity entity = world.create();
        test_component component { .has_run = true };
        world.insert(entity, component);
    }

    void create_two_entities(world& world)
    {
        entity entity1 = world.create();
        entity entity2 = world.create();
        test_component component { .has_run = true };
        world.insert(entity1, component);
        world.insert(entity2, component);
    }

} // namespace

TEST(ScheduleTest, Run_SystemsRanSequentially)
{
    // GIVEN
    schedule schedule;
    schedule.add_system(create).add_system(create_two_entities);

    world world;

    // WHEN
    schedule.run(world);

    // THEN
    sparse_set<test_component> components = world.components<test_component>();
    ASSERT_EQ(components.size(), 3);
}

} // namespace eecs::test
