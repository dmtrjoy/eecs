#include "world.hpp"

#include "sparse_set.hpp"

#include "gtest/gtest.h"

namespace misha::test {

/// A test component.
struct component {
    int x { 0 };
    int y { 0 };
    auto operator<=>(const component&) const = default;
};

TEST(WorldTest, CreateEntity_EntityIsIncremented)
{
    // GIVEN
    world world;

    // WHEN
    const entity entity1 = world.create_entity();
    const entity entity2 = world.create_entity();

    // THEN
    EXPECT_EQ(entity1, 0);
    EXPECT_EQ(entity2, entity1 + 1);
}

TEST(WorldTest, AddComponent_ComponentIsPresent)
{
    // GIVEN
    world world;
    const entity entity = world.create_entity();
    component pod;

    // WHEN
    world.add_component(entity, pod);
    sparse_set<component> components = world.get_components<component>();

    // THEN
    ASSERT_TRUE(components.contains(entity));
    EXPECT_EQ(components[entity], pod);
}

} // namespace misha::test
