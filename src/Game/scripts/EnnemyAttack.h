#pragma once
#include "PlayerMovement.h"
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class WaveManager;

class EnemyAttack : public IScript
{
public:

    EnemyAttack() = default;

    void OnStart() override;
    void OnCollisionEnter(Entity* other) override;
    void TakeDamage(float damages);

private:
    void Attack();
    void Die();

    PlayerMovement* PMScript;
    WaveManager* m_pWaveManager;
    float m_damage;
    float m_hp;
};

REGISTER_SCRIPT(EnemyAttack)
