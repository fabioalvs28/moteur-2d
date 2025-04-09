#pragma once
#include "Weapon.h"
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"
class Bow : public Weapon
{
public:

    Bow() = default;
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
    void OnAttack() override {};
};

REGISTER_SCRIPT(Bow)