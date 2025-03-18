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
    m_attackTime = 0.0;
    m_attackDelay = 2;
    m_attackDuration = 1;
    m_direction = sf::Vector2f(1.0, 0.0);
    m_attackDistance = 2.0;
}

void PlayerMovement::OnFixedUpdate()
{
    float speed = 2000.0f;
    owner->GetTransform()->position += movement * speed;
    movement = sf::Vector2f(0, 0);
}

void PlayerMovement::OnUpdate()
{
    m_time += Engine::GetGameManager()->GetTime()->GetDeltaTime();
    if (m_time >= m_attackDelay)
    {
        m_time -= m_attackDelay;
        Attack();
    if (isKeyPressed(sf::Keyboard::Key::D))
    {
        movement += owner->GetTransform()->right * Engine::GetDeltaTime();
    }
    if (isKeyPressed(sf::Keyboard::Key::Q))
    {
        movement -= owner->GetTransform()->right * Engine::GetDeltaTime();
    }
    if (isKeyPressed(sf::Keyboard::Key::S))
    {
        movement += owner->GetTransform()->up * Engine::GetDeltaTime();
    }
    if (isKeyPressed(sf::Keyboard::Key::Z))
    {
        movement -= owner->GetTransform()->up * Engine::GetDeltaTime();
    }
}

void PlayerMovement::OnDisable()
{
    
}

void PlayerMovement::Attack()
{
    if (m_isAttacking == true)
        return;

    m_isAttacking = true;
    Entity* attackRect = ObjectFactory::CreateEntity<Entity>();
    sf::Vector2f ownerPos = m_pOwner->GetTransform()->position;
    attackRect->GetTransform()->SetPosition(ownerPos.x + m_direction.x * m_attackDistance, ownerPos.y + m_direction.y * m_attackDistance);

    ObjectFactory::CreateComponent<SpriteRenderer>(attackRect, Resources::instance().DEFAULT_SPRITE);
}
