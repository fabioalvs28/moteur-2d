#include "pch.h"
#include "Boomerang.h"

#include "ObjectFactory.h"
#include "WeaponAttack.h"
#include "scripts/PlayerAttack.h"

void Boomerang::OnStart()
{
    m_attackDistance = 0.0f;
    m_TimeBeforeGoingBack = 2.0f;
    m_attackDelay = 10.0f;
    
    m_pGameManager = Engine::GetGameManager();
    mp_PlayerMovement = Engine::GetEntityByName("player")->GetScript<PlayerMovement>();
    m_velocity = 1000.0f;
    m_damages = 5.0f;
    m_lifeSpan = 10.0f;
    m_time = 0.0f;
    m_weaponType = TYPE_BOOMERANG;
    m_level = 1;
    m_direction = { 1.0f,1.0f};
    Engine::GetEntityByName("player")->GetScript<PlayerAttack>()->AddWeapon(this);
}

void Boomerang::OnFixedUpdate()
{
    for(Entity* const entity : m_Boomerang)
    {
        if(!entity->IsDestroyed())
        {
            TRANSFORM* eTransform = entity->GetTransform();
            eTransform->SetPosition(eTransform->position + (eTransform->direction * m_velocity * Engine::GetDeltaTime()));
        }

    }
}

void Boomerang::OnUpdate()
{
    // Supprime les entités détruites
    m_Boomerang.erase(
        std::remove_if(m_Boomerang.begin(), m_Boomerang.end(),
                       [](Entity* const entity) { return entity->IsDestroyed(); }),
        m_Boomerang.end()
    );

    m_time += Engine::GetDeltaTime();
    m_returnTime += Engine::GetDeltaTime();

    // Inverse la direction UNE SEULE FOIS quand le temps est écoulé
    if (!m_hasReturned && m_returnTime >= m_TimeBeforeGoingBack)
    {
        for (Entity* const entity : m_Boomerang)
        {
            entity->GetTransform()->direction *= -1.0f;
        }
        m_hasReturned = true;
    }

    if (m_time >= m_attackDelay)
    {
        OnAttack();
        m_time = 0.0f;
        m_returnTime = 0.0f;
        m_hasReturned = false; // réinitialise pour le prochain lancer
    }
}


void Boomerang::OnAttack()
{
    srand(time(NULL));
    
    Entity* boomerang = ObjectFactory::CreateEntity<Entity>(2);
    boomerang->GetTransform()->SetPosition(m_pOwner->GetTransform()->position);
    float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f;
    sf::Vector2f direction(std::cos(angle), std::sin(angle));
    boomerang->GetTransform()->direction = direction;
    CircleCollider* coll = ObjectFactory::CreateComponent<CircleCollider>(boomerang, 30.0f);
    coll->SetTrigger(true);
    ObjectFactory::CreateComponent<SpriteRenderer>(boomerang, Resources::instance().DEFAULT_SPRITE);
    ObjectFactory::AttachScript<WeaponAttack>(boomerang, m_damages, m_attackDistance, m_velocity, m_lifeSpan, m_direction);
    m_Boomerang.push_back(boomerang);
}

void Boomerang::Upgrade()
{
    
}
