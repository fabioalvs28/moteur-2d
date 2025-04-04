#pragma once
#include "PlayerMovement.h"
#include "scripts/Script.h"

class EnemyAttack : public IScript
{
public:
    EnemyAttack(PlayerMovement* playerHP);

    void OnStart() override;
    void OnTriggerEnter(Entity* other) override;
    void TakeDamage(float damage);
    
private:
    void Attack() const;
    void Die() const;
    
    float m_damage;
    float m_hp;
    PlayerMovement* HPp;
};
