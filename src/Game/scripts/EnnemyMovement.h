#pragma once
#include "scripts/Script.h"

class RigidBody2D;

class EnnemyMovement : public IScript
{
    
public:
    EnnemyMovement(Entity* player);
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;

private:
    TRANSFORM* mpTransform;
    sf::Vector2f movement;
    Entity* mpPlayer;
};
