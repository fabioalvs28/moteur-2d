#include "pch.h"
#include "EnnemyAttack.h"

#include "ObjectFactory.h"
#include "PlayerMovement.h"
#include "Experience.h"

void EnemyAttack::OnStart()
{
    m_damage = 1;
    PMScript = Engine::GetEntityByName("player")->GetScript<PlayerMovement>();

}

void EnemyAttack::Attack() const
{
    PMScript->TakeDamage(m_damage);
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
