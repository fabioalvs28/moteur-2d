#pragma once
#include "Weapon.h"
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class PlayerMovement;

class Sword : public Weapon
{
public:

    Sword() = default;

    void OnStart() override;
    void OnUpdate() override;
    void OnDisable() override {}
    void OnAttack() override;

private:
    PlayerMovement* mp_PlayerMovement;
};

REGISTER_SCRIPT(Sword)
