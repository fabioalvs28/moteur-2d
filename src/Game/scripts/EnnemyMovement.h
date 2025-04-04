#pragma once
#include "scripts/Script.h"

class RigidBody2D;

class EnemyMovement : public IScript
{
    
public:
    EnemyMovement(Entity* player);
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;

private:
    TRANSFORM* m_pTransform;
    sf::Vector2f m_movement;
    Entity* m_pPlayer;
};
