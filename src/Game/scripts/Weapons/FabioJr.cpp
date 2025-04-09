#include "pch.h"
#include "FabioJr.h"

#include "ObjectFactory.h"
#include "WeaponAttack.h"
#include "scripts/PlayerAttack.h"
#include "scripts/PlayerMovement.h"


void FabioJr::OnStart()
{
    m_attackDistance = 100.0f;
    m_attackDelay = 2.0f;
    m_pGameManager = Engine::GetGameManager();
    m_velocity = 3000.0f;
    m_damages = 5.0f;
    m_weaponType = TYPE_FABIOJR;
    m_level = 1;
    m_direction = { 1.0f,1.0f};
    
    Entity* Fabio = ObjectFactory::CreateEntity<Entity>(2);
    Fabio->GetTransform()->SetPosition(Engine::GetEntityByName("player")->GetTransform()->position);
    Fabio->GetTransform()->SetDirection(m_direction);
    ObjectFactory::CreateComponent<SpriteRenderer>(Fabio, Resources::instance().DEFAULT_SPRITE);
    CircleCollider* col = ObjectFactory::CreateComponent<CircleCollider>(Fabio, 50);
    col->SetTrigger(true);
    Engine::GetEntityByName("player")->GetScript<PlayerAttack>()->AddWeapon(this);
    camPos = Engine::GetEntityByName("camera")->GetTransform();
    
    ObjectFactory::AttachScript<WeaponAttack>(Fabio, m_damages, m_attackDistance, m_velocity, 1000000.0f, m_direction);
    m_Fabios.push_back(Fabio);
}

void FabioJr::OnFixedUpdate()
{
    for(Entity* const entity : m_Fabios)
    {
        TRANSFORM* eTransform = entity->GetTransform();
        eTransform->SetPosition(eTransform->position + (eTransform->direction * m_velocity * Engine::GetDeltaTime()));
    }
        
}

void FabioJr::OnUpdate()
{
    for(Entity* const entity : m_Fabios)
    {
        TRANSFORM* eTransform = entity->GetTransform();
        
        sf::Vector2f windowPos = camPos->position;
        sf::Vector2u windowSize = Engine::GetRenderWindow()->getSize();

        sf::Vector2f colliderCenter = entity->GetComponent<Collider2D>()->GetCenter();

        if (colliderCenter.x <= windowPos.x) {
            eTransform->direction.x = std::abs(eTransform->direction.x);
            eTransform->position.x = windowPos.x; 
        }

        if (colliderCenter.x >= windowPos.x + windowSize.x) {
            eTransform->direction.x = -std::abs(eTransform->direction.x); 
            eTransform->position.x = windowPos.x + windowSize.x; 
        }

        if (colliderCenter.y <= windowPos.y) {
            eTransform->direction.y = std::abs(eTransform->direction.y); 
            eTransform->position.y = windowPos.y; 
        }

        if (colliderCenter.y >= windowPos.y + windowSize.y) {
            eTransform->direction.y = -std::abs(eTransform->direction.y); 
            eTransform->position.y = windowPos.y + windowSize.y; 
        }
    }

}

void FabioJr::Upgrade()
{
    m_level++;
    Entity* Fabio = ObjectFactory::CreateEntity<Entity>(2);
    Fabio->GetTransform()->SetPosition(Engine::GetEntityByName("player")->GetTransform()->position);
    Fabio->GetTransform()->SetDirection(m_direction);
    ObjectFactory::CreateComponent<SpriteRenderer>(Fabio, Resources::instance().DEFAULT_SPRITE);
    CircleCollider* col = ObjectFactory::CreateComponent<CircleCollider>(Fabio, 50);
    col->SetTrigger(true);
    ObjectFactory::AttachScript<WeaponAttack>(Fabio, m_damages, m_attackDistance, m_velocity, 1000000.0f, m_direction);
    m_Fabios.push_back(Fabio);
    m_velocity *= 1.10f;
}
