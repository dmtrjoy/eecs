#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include <string_view>

namespace engine {

class Scene {
public:
    explicit Scene(std::string_view name);

private:
    std::string_view m_name;
};

}

#endif // !ENGINE_SCENE_H
