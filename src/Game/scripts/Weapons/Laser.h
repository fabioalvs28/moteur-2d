#pragma once
#include "Weapon.h"
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"
#include "scripts/PlayerMovement.h"

class Laser : public Weapon
{
public:

    Laser() = default;
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
    void OnAttack() override;
    void Upgrade() override;
    
private:
    PlayerMovement* mp_PlayerMovement;
    float m_width;
    float m_height;
};

REGISTER_SCRIPT(Laser)