#pragma once
#include "PlayerMovement.h"
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class EnemyAttack : public IScript
{
public:

    EnnemyAttack() = default;

    void OnStart() override;
    void Attack();
    void OnTriggerEnter(Entity* other) override;

private:
    void Attack() const;
    void Die() const;

    PlayerMovement* PMScript;
    float m_damage;
    float m_hp;
};

REGISTER_SCRIPT(EnnemyAttack)
