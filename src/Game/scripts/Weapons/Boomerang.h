#pragma once
#include "Weapon.h"
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"
#include "scripts/PlayerMovement.h"

class Boomerang : public Weapon
{
public:
    Boomerang() = default;
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override {}
    void OnAttack() override;
    void Upgrade() override;
private:
    PlayerMovement* mp_PlayerMovement;
    std::vector<Entity*> m_Boomerang;
    float m_TimeBeforeGoingBack;
    float m_returnTime;
    bool m_hasReturned;
};

REGISTER_SCRIPT(Boomerang)