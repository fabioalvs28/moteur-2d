#pragma once
#include "PlayerMovement.h"
#include "scripts/Script.h"

class EnnemyAttack : public IScript
{
public:
    EnnemyAttack(PlayerMovement* playerHP);

    void OnStart() override;
    void Attack(Entity* other);
    void OnTriggerEnter(Entity* other) override;

private:
    float mDamage;
    PlayerMovement* HPp;
};
