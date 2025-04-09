#pragma once
#include "Weapon.h"
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class Bomb : public Weapon
{
public:

    Bomb() = default;
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
    void OnAttack() override;
    void Upgrade() override;
private:
    TRANSFORM* mp_CamPos;
    float m_radius;
};

REGISTER_SCRIPT(Bomb)