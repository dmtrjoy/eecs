#ifndef ENGINE_SCENE_MANAGER_H
#define ENGINE_SCENE_MANAGER_H

#include "scene.hpp"
#include "singleton.hpp"

namespace engine {

class SceneManager final : public Singleton<SceneManager> {
public:
    void loadScene();
};

}

#endif // !ENGINE_SCENE_MANAGER_H
