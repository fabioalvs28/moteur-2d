#include "pch.h"
#include "EnnemyAttack.h"

#include "PlayerMovement.h"


void EnnemyAttack::OnStart()
{
    PMScript = Engine::GetEntityByName("player")->GetScript<PlayerMovement>();
}

void EnnemyAttack::Attack()
{
    PMScript->SetHP(PMScript->GetHP() - mDamage);
}

void EnnemyAttack::OnTriggerEnter(Entity* other)
{
    if(other->IsTag(Entity::Tag::PLAYER))
    {
        Attack();
    }
}

