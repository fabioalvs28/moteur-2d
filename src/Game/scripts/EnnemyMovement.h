#pragma once
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class EnemyMovement : public IScript
{
    
public:
    EnnemyMovement() = default;
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;

private:
    TRANSFORM* mpTransform;
    sf::Vector2f movement;
    TRANSFORM* mpPlayerTransform;
};

REGISTER_SCRIPT(EnnemyMovement)