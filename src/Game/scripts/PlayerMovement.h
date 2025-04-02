#pragma once
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class PlayerMovement : public IScript
{
    
public:
    PlayerMovement();
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnCollisionEnter(Entity* other) override;
    void OnUpdate() override;
    void OnDisable() override;
    void SetHP(float hp) { HP = hp; }
    float GetHP() { return HP; }

private:
    TRANSFORM* mTransform;
    sf::Vector2f movement;
    float HP;
};

REGISTER_SCRIPT(PlayerMovement)