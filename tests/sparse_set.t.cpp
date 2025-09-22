#include "sparse_set.hpp"

#include "types.hpp"

#include "gtest/gtest.h"

namespace eecs::test {

TEST(SparseSetTest, Insert_ValueIsPresent)
{
    // GIVEN
    sparse_set<float> set;
    const u32 id = 42;
    const float value = 100.0;

    // WHEN
    set.insert(id, value);

    // THEN
    ASSERT_TRUE(set.contains(id));
    EXPECT_EQ(set[id], value);
    EXPECT_EQ(set.size(), 1);
}

TEST(SparseSetTest, Insert_ForExistingId_ValueIsUpdated)
{
    // GIVEN
    const u32 id = 42;
    float value = 100.0;

    sparse_set<float> set;
    set.insert(id, value);

    // WHEN
    value += 1.0;
    set.insert(id, value);

    // THEN
    ASSERT_TRUE(set.contains(id));
    EXPECT_EQ(set[id], value);
    EXPECT_EQ(set.size(), 1);
}

TEST(SparseSetTest, Erase_ValueIsRemoved)
{
    // GIVEN
    const u32 id = 42;
    const float value = 100.0;

    sparse_set<float> set;
    set.insert(id, value);

    // WHEN
    set.erase(id);

    // THEN
    EXPECT_FALSE(set.contains(id));
    EXPECT_TRUE(set.empty());
}

} // namespace eecs::test
