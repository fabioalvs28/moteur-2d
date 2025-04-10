#include "pch.h"
#include "Laser.h"

#include "ObjectFactory.h"
#include "WeaponAttack.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "scripts/PlayerAttack.h"

void Laser::OnStart()
{
    mp_PlayerMovement = Engine::GetEntityByName("player")->GetScript<PlayerMovement>();
    m_attackDistance = 10.0f;
    m_attackDelay = 5.0f;
    m_time = 0.0f;
    m_width = 1000.0f;
    m_height = 100.0f;
    m_pGameManager = Engine::GetGameManager();
    m_velocity = 0.0f;
    m_lifeSpan = 1.0f;
    m_damages = 5.0f;
    m_weaponType = TYPE_LASER;
    m_level = 1;
    Engine::GetEntityByName("player")->GetScript<PlayerAttack>()->AddWeapon(this);
}

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

void Laser::OnAttack()
{
        Entity* attackRect = ObjectFactory::CreateEntity<Entity>();
        sf::Vector2f futurePos = m_pOwner->GetTransform()->position + m_direction * m_attackDistance;
        attackRect->GetTransform()->position = futurePos + sf::Vector2f(550.0f * m_direction.x,350.0f * m_direction.y);
        SpriteRenderer* sr = ObjectFactory::CreateComponent<SpriteRenderer>(attackRect, Resources::instance().DEFAULT_SPRITE);

        if(m_direction.x == -1 || m_direction.x  == 1)
        {
            AABBCollider* coll =  ObjectFactory::CreateComponent<AABBCollider>(attackRect,0,0,m_width,m_height);
            coll->SetTrigger(true);
        }
        else
        {
            AABBCollider* coll =  ObjectFactory::CreateComponent<AABBCollider>(attackRect,0,0,m_height,m_width);
            coll->SetTrigger(true);
        }

        ObjectFactory::AttachScript<WeaponAttack>(attackRect, m_damages, m_attackDistance, m_velocity, m_lifeSpan, m_direction);
    
}

void Laser::Upgrade()
{
    m_width *= 1.1f;
    m_level++;
}


