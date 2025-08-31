#include "schedule.hpp"

#include "entity.hpp"
#include "world.hpp"

#include "gtest/gtest.h"

namespace eecs::test {

namespace {

    struct test_component {
        bool has_run = false;
    };

    void create_entity(world& world)
    {
        entity entity = world.create_entity();
        test_component component { .has_run = true };
        world.add_component(entity, component);
    }

    void create_two_entities(world& world)
    {
        entity entity1 = world.create_entity();
        entity entity2 = world.create_entity();
        test_component component { .has_run = true };
        world.add_component(entity1, component);
        world.add_component(entity2, component);
    }

} // namespace

TEST(ScheduleTest, Run_SystemsRanSequentially)
{
    // GIVEN
    schedule schedule;
    schedule.add_system(create_entity).add_system(create_two_entities);

    world world;

    // WHEN
    schedule.run(world);

    // THEN
    sparse_set<test_component> components = world.components<test_component>();
    ASSERT_EQ(components.size(), 3);
}

} // namespace eecs::test
