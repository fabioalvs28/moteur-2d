#include "pch.h"
#include "Sword.h"

#include "ObjectFactory.h"
#include "Managers/GameManager.h"
#include "Transform.h"
#include "WeaponAttack.h"
#include "../EnnemyAttack.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "scripts/PlayerAttack.h"


void Sword::OnStart()
{
    mp_PlayerMovement = Engine::GetEntityByName("player")->GetScript<PlayerMovement>();
    m_attackDistance = 100.0f;
    m_attackDelay = 2.0f;
    m_time = 0.0f;
    m_pGameManager = Engine::GetGameManager();
    m_velocity = 0.0f;
    m_lifeSpan = 2.0f;
    m_damages = 5.0f;
    m_weaponType = TYPE_SWORD;
    m_level = 1;
    Engine::GetEntityByName("player")->GetScript<PlayerAttack>()->AddWeapon(this);
}

void Sword::OnUpdate()
{
    m_direction = mp_PlayerMovement->GetDirection();
    m_time += Engine::GetDeltaTime();
    if(m_time >= m_attackDelay)
    {
        OnAttack();
        m_time = 0.0f;
    }
}

void Sword::OnAttack()
{
    if(m_level == 1)
    {
        Entity* attackRect = ObjectFactory::CreateEntity<Entity>();
        sf::Vector2f futurePos = m_pOwner->GetTransform()->position + m_direction * m_attackDistance;
        attackRect->GetTransform()->position = futurePos;
        SpriteRenderer* sr = ObjectFactory::CreateComponent<SpriteRenderer>(attackRect, Resources::instance().DEFAULT_SPRITE);
        AABBCollider* coll =  ObjectFactory::CreateComponent<AABBCollider>(attackRect,0,0,100,100);
        coll->SetTrigger(true);

        ObjectFactory::AttachScript<WeaponAttack>(attackRect, m_damages, m_attackDistance, 0.0, m_direction);
        
        // sr->Image->setOrigin({ sr->Image->getTexture().getSize().x * 0.5f, sr->Image->getTexture().getSize().y * 0.5f });


        // float rotation = atan2(m_direction.y, m_direction.x);
        // attackRect->GetTransform()->rotation = sf::radians(rotation);
    }
    
}