#include "pch.h"
#include "PlayerMovement.h"
#include "Managers/GameManager.h"

#include "ObjectFactory.h"
#include "Resources.h"
#include "Transform.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"
#include "scripts/Weapons/Sword.h"

PlayerMovement::PlayerMovement(Entity* camera)
{
    m_pCamera = camera;
}

void PlayerMovement::OnStart()
{
    m_time = 0;
    m_attackDelay = 2.0f;
    m_attackDistance = 100.0f;
    m_direction = sf::Vector2f(1.0, 0.0);
    m_pGameManager = Engine::GetGameManager();
    m_speed = 100;
    m_rw = Engine::GetRenderWindow();
    m_transform = m_pOwner->GetTransform();
    m_hp = 10;
}

void PlayerMovement::OnFixedUpdate()
{
    m_transform->SetPosition(m_transform->position.x + m_movement.x * m_speed, m_transform->position.y + m_movement.y * m_speed);
    m_movement = sf::Vector2f(0, 0);
}

void PlayerMovement::OnCollisionEnter(Entity* other)
{
    std::cout << "Collision Enter" << std::endl;
}

void PlayerMovement::OnUpdate()
{
    m_pCamera->GetTransform()->position = m_transform->position - sf::Vector2f(960, 540);
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
    Entity* attackRect = ObjectFactory::CreateEntity<Entity>();
    RenderWindow* pWindow = Engine::GetRenderWindow();

    ObjectFactory::CreateComponent<SpriteRenderer>(attackRect, Resources::instance().DEFAULT_SPRITE);
    ObjectFactory::AttachScript<Sword>(attackRect, m_direction);
    sf::Vector2f ownerPos = m_pOwner->GetTransform()->position;
    attackRect->GetTransform()->position = sf::Vector2f(ownerPos.x + m_direction.x * m_attackDistance, ownerPos.y + m_direction.y * m_attackDistance);
}
