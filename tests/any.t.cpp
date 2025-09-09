#include "any.hpp"

#include <typeindex>

#include "gtest/gtest.h"

namespace eecs::test {

TEST(AnyTest, DefaultConstructor)
{
    // GIVEN
    // ...

    // WHEN
    const any any {};

    // THEN
    EXPECT_FALSE(any.has_value());
    EXPECT_EQ(any.type(), std::type_index(typeid(void)));
}

TEST(AnyTest, CopyConstructor)
{
    // GIVEN
    const any any1 { 100.0 };

    // WHEN
    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    const any any2 { any1 };

    // THEN
    EXPECT_EQ(any1, any2);
}

} // namespace eecs::test
