#include "pch.h"
#include "EnnemyAttack.h"

#include "ObjectFactory.h"
#include "PlayerMovement.h"
#include "Experience.h"

EnemyAttack::EnemyAttack(PlayerMovement* playerHP): m_hp(1)
{
    m_damage = 1;
    HPp = playerHP;
}

void EnemyAttack::OnStart()
{
    m_damage = 1;
    PMScript = Engine::GetEntityByName("player")->GetScript<PlayerMovement>();

}

void EnnemyAttack::Attack()
{
    PMScript->SetHP(PMScript->GetHP() - mDamage);
}

void EnemyAttack::Die() const
{
    Entity* pXpOrb = ObjectFactory::CreateEntity<Entity>();
    pXpOrb->SetTag(Entity::Tag::XP);
    ObjectFactory::CreateComponent<SpriteRenderer>(pXpOrb, Resources::instance().EXP);
    CircleCollider* coll = ObjectFactory::CreateComponent<CircleCollider>(pXpOrb);
    coll->SetTrigger(true);
    ObjectFactory::AttachScript<Experience>(pXpOrb);
    m_pOwner->Destroy();
}

void EnemyAttack::OnCollisionEnter(Entity* other)
{
    if(other->IsTag(Entity::Tag::PLAYER))
    {
        Attack();
    }
}

void EnemyAttack::TakeDamage(float damage)
{
    m_hp -= damage;
    if (m_hp <= 0)
        Die();
}
