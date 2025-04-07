#pragma once
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class EnemyMovement : public IScript
{
    
public:
    EnemyMovement() = default;
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;

private:
    TRANSFORM* m_pTransform;
    sf::Vector2f m_movement;
    TRANSFORM* m_pPlayerTransform;
};

REGISTER_SCRIPT(EnemyMovement)