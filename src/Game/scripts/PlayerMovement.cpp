#include "pch.h"
#include "PlayerMovement.h"
#include "Managers/GameManager.h"

#include "ObjectFactory.h"
#include "Resources.h"
#include "Transform.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"

void PlayerMovement::OnStart()
{
    m_isAttacking = false;
    m_time = 0;
    m_attackTime = 0.0f;
    m_attackDelay = 2;
    m_attackDuration = 1;
    m_direction = sf::Vector2f(1.0, 0.0);
    m_attackDistance = 100.0f;
    m_pGameManager = Engine::GetGameManager();
    m_speed = 500.0f;
    m_rw = Engine::GetRenderWindow();
}

void PlayerMovement::OnFixedUpdate()
{
    TRANSFORM* ownerTransform = m_pOwner->GetTransform();
    ownerTransform->SetPosition(ownerTransform->position.x + m_movement.x * m_speed + m_rw->GetWindowHeight(), ownerTransform->position.x + m_movement.x * m_speed + m_rw->GetWindowHeight());
    m_movement = sf::Vector2f(0, 0);
}

void PlayerMovement::OnUpdate()
{
    m_time += m_pGameManager->GetTime()->GetDeltaTime();
    if (m_time >= m_attackDelay)
    {
        m_time -= m_attackDelay;
        Attack();
    }

    if (isKeyPressed(sf::Keyboard::Key::D))
    {
        m_movement += m_pOwner->GetTransform()->right * Engine::GetDeltaTime();
        m_direction = sf::Vector2f(1.0, 0.0);
    }
    if (isKeyPressed(sf::Keyboard::Key::Q))
    {
        m_movement -= m_pOwner->GetTransform()->right * Engine::GetDeltaTime();
        m_direction = sf::Vector2f(-1.0, 0.0);
    }
    if (isKeyPressed(sf::Keyboard::Key::S))
    {
        m_movement += m_pOwner->GetTransform()->up * Engine::GetDeltaTime();
        m_direction = sf::Vector2f(0.0, 1.0);
    }
    if (isKeyPressed(sf::Keyboard::Key::Z))
    {
        m_movement -= m_pOwner->GetTransform()->up * Engine::GetDeltaTime();
        m_direction = sf::Vector2f(0.0, -1.0);
    }
}

void PlayerMovement::OnDisable()
{
    
}

void PlayerMovement::Attack()
{
    //if (m_isAttacking == true)
    //    return;
        
    m_isAttacking = true;
    Entity* attackRect = ObjectFactory::CreateEntity<Entity>();
    sf::Vector2f ownerPos = m_pOwner->GetTransform()->position;
    attackRect->GetTransform()->SetPosition(ownerPos.x + m_direction.x * m_attackDistance, ownerPos.y + m_direction.y * m_attackDistance);

    SpriteRenderer* pSp = ObjectFactory::CreateComponent<SpriteRenderer>(attackRect, Resources::instance().DEFAULT_SPRITE);
    pSp->Image->setScale({ 10,10 });
}
