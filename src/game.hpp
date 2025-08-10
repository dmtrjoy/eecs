#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include "scene_manager.hpp"
#include "singleton.hpp"

namespace engine {

class Game final : public Singleton<Game> {
public:
    void initialize();
    void startup();
    void shutdown();

private:
    SceneManager& m_sceneManager = SceneManager::getInstance();
};

}

#endif // !ENGINE_GAME_H
