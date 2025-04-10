#pragma once
#include "Weapon.h"
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class BodyCount : public Weapon
{
public:

    void OnStart() override;
    void OnFixedUpdate() override;
    void Upgrade()override;
    void OnAttack() override {};

private:
    
    TRANSFORM* mp_OwnerTransform;
    float m_radius;
    Entity* mp_aura;
};

REGISTER_SCRIPT(BodyCount);