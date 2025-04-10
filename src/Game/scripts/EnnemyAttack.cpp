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
    m_hp = 500.0f;
}

void EnemyAttack::Attack()
{
    Engine::GetEntityByName("player")->GetScript<PlayerMovement>()->TakeDamage(m_damage);
}

void EnemyAttack::Die()
{
    Entity* pXpOrb = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<SpriteRenderer>(pXpOrb, Resources::instance().EXP);
    CircleCollider* coll = ObjectFactory::CreateComponent<CircleCollider>(pXpOrb, 10);
    pXpOrb->GetTransform()->SetPosition(m_pOwner->GetTransform()->position);
    ObjectFactory::AttachScript<Experience>(pXpOrb);
    coll->SetTrigger(true);
    pXpOrb->SetTag(Entity::Tag::XP);
    m_pWaveManager->Decrease();
    m_pOwner->Destroy();
}

void EnemyAttack::OnTriggerStay(Entity* other)
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
