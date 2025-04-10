#include "pch.h"
#include "BodyCount.h"

#include "ObjectFactory.h"
#include "Resources.h"
#include "WeaponAttack.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Colliders/CircleCollider.h"
#include "scripts/PlayerAttack.h"

void BodyCount::OnStart()
{
    m_attackDistance = 0.0f;
    m_attackDelay = 2.0f;
    m_pGameManager = Engine::GetGameManager();
    m_velocity = 0.0f;
    m_damages = 5.0f;
    m_weaponType = TYPE_DEO;
    m_level = 1;
    m_direction = { 1.0f,1.0f};
    m_radius = 125;
    
    mp_OwnerTransform = m_pOwner->GetTransform();
    mp_aura = ObjectFactory::CreateEntity<Entity>(0);
    mp_aura->SetTag(Entity::Tag::PLAYER);
    mp_aura->GetTransform()->SetPosition(m_pOwner->GetTransform()->position);
    ObjectFactory::CreateComponent<SpriteRenderer>(mp_aura, Resources::instance().DEFAULT_SPRITE);
    CircleCollider* col = ObjectFactory::CreateComponent<CircleCollider>(mp_aura, m_radius);
    col->SetTrigger(true);
    Engine::GetEntityByName("player")->GetScript<PlayerAttack>()->AddWeapon(this);
    ObjectFactory::AttachScript<WeaponAttack>(mp_aura, m_damages, m_attackDistance, m_velocity, 10000000.0f, m_direction);
}

void BodyCount::OnFixedUpdate()
{
    mp_aura->GetTransform()->SetPosition(m_pOwner->GetTransform()->position);
}

void BodyCount::Upgrade()
{
    m_level++;
    m_radius *= 1.1f;
    mp_aura->GetComponent<CircleCollider>()->SetRadius(m_radius);
}