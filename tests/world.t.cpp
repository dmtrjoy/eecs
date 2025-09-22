#include "world.hpp"

#include "sparse_set.hpp"

#include "gtest/gtest.h"

namespace eecs::test {

// A 2D texture component. Only for testing purposes.
struct texture2 {
    int id;
};

/// A 2D vector component. Only for testing purposes.
struct vec2 {
    float x { 0.0 };
    float y { 0.0 };
    auto operator<=>(const vec2&) const = default;
};

/// A window resource. Only for testing purposes.
struct window_resource {
    int width { 0 };
    int height { 0 };
};

class WorldTest : public testing::Test {
protected:
    world world;
};

TEST_F(WorldTest, CreateEntity_EntityIsIncremented)
{
    // GIVEN
    // ...

    // WHEN
    const entity entity1 { world.create() };
    const entity entity2 { world.create() };

    // THEN
    EXPECT_EQ(entity1, 0);
    EXPECT_EQ(entity2, entity1 + 1);
}

TEST_F(WorldTest, AddComponent_ComponentIsPresent)
{
    // GIVEN
    const entity entity { world.create() };
    vec2 vec;

    // WHEN
    world.insert(entity, vec);
    const sparse_set<vec2>& vecs { world.components<vec2>() };

    // THEN
    ASSERT_TRUE(vecs.contains(entity));
    EXPECT_EQ(vecs[entity], vec);
}

TEST_F(WorldTest, AddResource_ResourceIsPresent)
{
    // GIVEN
    const int width { 800 };
    const int height { 600 };

    // WHEN
    world.add_resource<window_resource>(width, height);
    const auto& window { world.resource<window_resource>() };

    // THEN
    EXPECT_EQ(window.width, width);
    EXPECT_EQ(window.height, height);
}

TEST_F(WorldTest, AddResource_ExistingResource_ResourceIsUpdated)
{
    // GIVEN
    const int width { 100 };
    const int height { 100 };

    // WHEN
    world.add_resource<window_resource>(width, height);
    const auto& window { world.resource<window_resource>() };

    // THEN
    EXPECT_EQ(window.width, width);
    EXPECT_EQ(window.height, height);
}

TEST_F(WorldTest, View_ComponentsAreUpdated)
{
    // GIVEN
    const vec2 viewed_vec { .x = 100.0, .y = 100.0 };

    /// WHEN
    world.view<vec2>(
        [viewed_vec](const entity entity, vec2& vec) { vec = viewed_vec; });
    const sparse_set<vec2>& vecs = { world.components<vec2>() };

    // THEN
    for (const auto& vec : vecs) {
        EXPECT_EQ(vec, viewed_vec);
    }
}

} // namespace eecs::test
