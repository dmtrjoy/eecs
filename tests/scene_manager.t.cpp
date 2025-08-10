#include "scene_manager.hpp"
#include "gtest/gtest.h"

namespace engine::test {

TEST(SceneManagerTest, GetInstance)
{
    // GIVEN
    SceneManager& sceneManagerA = SceneManager::getInstance();

    // WHEN
    // SceneManager& sceneManagerB = SceneManager::getInstance();

    // THEN
    // ASSERT_EQ(sceneManagerA, sceneManagerB);
}

}
