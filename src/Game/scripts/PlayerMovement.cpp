#include "pch.h"
#include "PlayerMovement.h"
#include "Managers/GameManager.h"

#include "ObjectFactory.h"
#include "Resources.h"
#include "Transform.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"

PlayerMovement::PlayerMovement(Entity* camera)
{
    m_pCamera = camera;
}

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
    m_speed = 1000.0f;
    m_rw = Engine::GetRenderWindow();
    mTransform = m_pOwner->GetTransform();
    HP = 10;
}

void PlayerMovement::OnFixedUpdate()
{
    TRANSFORM* ownerTransform = m_pOwner->GetTransform();
    ownerTransform->SetPosition(ownerTransform->position.x + m_movement.x * m_speed, ownerTransform->position.y + m_movement.y * m_speed);
    m_movement = sf::Vector2f(0, 0);
    m_pCamera->GetTransform()->SetPosition(ownerTransform->position.x - Engine::GetRenderWindow()->getSize().x * 0.5f, ownerTransform->position.y - Engine::GetRenderWindow()->getSize().y * 0.5f);
}

void PlayerMovement::OnCollisionEnter(Entity* other)
{
    std::cout << "Collision Enter" << std::endl;
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
    RenderWindow* pWindow = Engine::GetRenderWindow();

    ObjectFactory::CreateComponent<SpriteRenderer>(attackRect, Resources::instance().DEFAULT_SPRITE);
    sf::Vector2f ownerPos = m_pOwner->GetTransform()->position;
    attackRect->GetTransform()->position = sf::Vector2f(ownerPos.x + m_direction.x * m_attackDistance, ownerPos.y + m_direction.y * m_attackDistance);
}
