#include "pch.h"
#include "EnnemyAttack.h"

#include "PlayerMovement.h"


void EnnemyAttack::OnStart()
{
    //l = Engine::GetEntityByName("player")->GetScript<PlayerMovement>();
}

void EnnemyAttack::Attack()
{
    //l->SetHP(l->GetHP() - mDamage);
}

void EnnemyAttack::OnTriggerEnter(Entity* other)
{
    if(other->IsTag(Entity::Tag::PLAYER))
    {
        Attack();
    }
}

