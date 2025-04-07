#pragma once
#include "PlayerMovement.h"
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class EnemyAttack : public IScript
{
public:

    EnemyAttack() = default;

    void OnStart() override;
    void OnCollisionEnter(Entity* other) override;
    void TakeDamage(float damages);

private:
    void Attack() const;
    void Die() const;

    PlayerMovement* PMScript;
    float m_damage;
    float m_hp;
};

REGISTER_SCRIPT(EnemyAttack)
