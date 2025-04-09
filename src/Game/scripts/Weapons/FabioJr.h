#pragma once
#include "Weapon.h"
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"
class FabioJr : public Weapon
{
public:

    FabioJr() = default;
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override {}
    void OnAttack() override {};
    void Upgrade() override;

private:
    std::vector<Entity*> m_Fabios;
    TRANSFORM* camPos;
    TRANSFORM* mp_OwnerTransform;
};

REGISTER_SCRIPT(FabioJr)