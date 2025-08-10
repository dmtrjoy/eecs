#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

namespace engine {

class Entity {
public:
    Entity();
    Entity(Entity&&) = default;
    Entity(const Entity&) = default;
    Entity& operator=(Entity&&) = default;
    Entity& operator=(const Entity&) = default;
    virtual ~Entity();

    virtual void ready() const = 0;

    virtual void update(float deltaTime) const = 0;

    virtual void fixedUpdate(float deltaTime) const = 0;

    virtual void draw() const = 0;
};

}

#endif // !ENGINE_ENTITY_H
