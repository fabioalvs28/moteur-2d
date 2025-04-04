#pragma once
#include "PlayerMovement.h"
#include "scripts/Script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class EnnemyAttack : public IScript
{
public:
    EnnemyAttack() = default;

    void OnStart() override;
    void Attack();
    void OnTriggerEnter(Entity* other) override;

private:
    float mDamage;
    PlayerMovement* l;
};

REGISTER_SCRIPT(EnnemyAttack)
