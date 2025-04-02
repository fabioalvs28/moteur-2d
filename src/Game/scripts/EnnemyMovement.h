#pragma once
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class EnnemyMovement : public IScript
{
    
public:
    EnnemyMovement() = default;
    EnnemyMovement(Entity* player);
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;

private:
    TRANSFORM* mpTransform;
    sf::Vector2f movement;
    Entity* mpPlayer;
};

REGISTER_SCRIPT(EnnemyMovement)