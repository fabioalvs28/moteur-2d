#include "pch.h"
#include "Laser.h"

#include "ObjectFactory.h"
#include "WeaponAttack.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "scripts/PlayerAttack.h"

void Laser::OnUpdate()
{
    m_direction = mp_PlayerMovement->GetDirection();
    m_time += Engine::GetDeltaTime();
    if(m_time >= m_attackDelay)
    {
        OnAttack();
        m_time = 0.0f;
    }
}

void Laser::OnStart()
{
    mp_PlayerMovement = Engine::GetEntityByName("player")->GetScript<PlayerMovement>();
    m_attackDistance = 10.0f;
    m_attackDelay = 5.0f;
    m_time = 0.0f;
    m_pGameManager = Engine::GetGameManager();
    m_velocity = 0.0f;
    m_lifeSpan = 1.0f;
    m_damages = 5.0f;
    m_weaponType = TYPE_LASER;
    m_level = 1;
    Engine::GetEntityByName("player")->GetScript<PlayerAttack>()->AddWeapon(this);
}

void Laser::OnAttack()
{
    if(m_level == 1)
    {
        Entity* attackRect = ObjectFactory::CreateEntity<Entity>();
        sf::Vector2f futurePos = m_pOwner->GetTransform()->position + m_direction * m_attackDistance;
        attackRect->GetTransform()->position = futurePos + sf::Vector2f(550.0f * m_direction.x,350.0f * m_direction.y);
        SpriteRenderer* sr = ObjectFactory::CreateComponent<SpriteRenderer>(attackRect, Resources::instance().DEFAULT_SPRITE);

        if(m_direction.x == -1 || m_direction.x  == 1)
        {
            AABBCollider* coll =  ObjectFactory::CreateComponent<AABBCollider>(attackRect,0,0,1000,100);
            coll->SetTrigger(true);
        }
        else
        {
            AABBCollider* coll =  ObjectFactory::CreateComponent<AABBCollider>(attackRect,0,0,100,1000);
            coll->SetTrigger(true);
        }

        ObjectFactory::AttachScript<WeaponAttack>(attackRect, m_damages, m_attackDistance, m_velocity, m_lifeSpan, m_direction);
        
        // sr->Image->setOrigin({ sr->Image->getTexture().getSize().x * 0.5f, sr->Image->getTexture().getSize().y * 0.5f });
        // float rotation = atan2(m_direction.y, m_direction.x);
        // attackRect->GetTransform()->rotation = sf::radians(rotation);
    }
}


