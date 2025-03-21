#include "pch.h"
#include "EnnemyAttack.h"

#include "PlayerMovement.h"

EnnemyAttack::EnnemyAttack(PlayerMovement* playerHP)
{
    HPp = playerHP;
}

void EnnemyAttack::OnStart()
{
    mDamage = 1;
}

void EnnemyAttack::Attack(Entity* other)
{
    HPp->SetHP(HPp->GetHP() - mDamage);
}

void EnnemyAttack::OnTriggerEnter(Entity* other)
{
    if(other->IsTag(Entity::Tag::PLAYER))
    {
        Attack(other);
    }
}
