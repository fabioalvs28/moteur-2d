#include "pch.h"
#include "EnnemyAttack.h"

#include "ObjectFactory.h"
#include "PlayerMovement.h"
#include "Experience.h"
#include "WaveManager.h"

void EnemyAttack::OnStart()
{
    m_damage = 1;
    PMScript = Engine::GetEntityByName("player")->GetScript<PlayerMovement>();
    m_pWaveManager = Engine::GetEntityByName("WaveManager")->GetScript<WaveManager>();
    m_hp = 1.0f;
}

void EnemyAttack::Attack() const
{
    if(PMScript)
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
    m_pWaveManager->Decrease();
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
