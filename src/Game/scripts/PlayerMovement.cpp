#include "pch.h"
#include "PlayerMovement.h"

#include "Experience.h"
#include "Managers/GameManager.h"

#include "ObjectFactory.h"
#include "Resources.h"
#include "Transform.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/ui/ProgressBar.h"
#include "ECS/Components/Animator.h"
#include "scripts/Weapons/Sword.h"

void PlayerMovement::OnStart()
{
    m_experience = 0;
    m_maxExp = 10;
    m_time = 0;
    m_attackDelay = 1.5f;
    m_attackDistance = 100.0f;
    m_direction = sf::Vector2f(1.0, 0.0);
    m_speed = 200.0f;
    m_hp = 10.0f;
    m_rw = Engine::GetRenderWindow();
    m_pTransform = m_pOwner->GetTransform();
    m_pGameManager = Engine::GetGameManager();
    m_pCamera = Engine::GetEntityByName("camera");

    sf::Vector2f scaleExp = sf::Vector2f(8.0f, 3.0f);
    Entity* UI_ExpBar = ObjectFactory::CreateEntity<Entity>();
    m_pExpBar = ObjectFactory::CreateComponent<ProgressBar>(UI_ExpBar, Resources::instance().BAR_CONTAINER, Resources::instance().BAR_EXP,
        sf::Vector2f(m_rw->GetWindowWidth() / 2 - Resources::instance().BAR_CONTAINER->getTexture().getSize().x * scaleExp.x / 2, 20.0f), sf::Vector2f(4.5f * scaleExp.x, 4.0f * scaleExp.y));
    
    m_pExpBar->Scale = sf::Vector2f(scaleExp.x, scaleExp.y);

    sf::Vector2f scaleHP = sf::Vector2f(3.5f, 2.0f);
    Entity* UI_HealthBar = ObjectFactory::CreateEntity<Entity>();
    m_pHealthBar = ObjectFactory::CreateComponent<ProgressBar>(UI_HealthBar, Resources::instance().BAR_CONTAINER, Resources::instance().BAR_HEALTH,
        sf::Vector2f(10.0f, 30.0f), sf::Vector2f(4.5f * scaleHP.x, 4.0f * scaleHP.y));

    m_pHealthBar->Scale = sf::Vector2f(scaleHP.x, scaleHP.y);

    m_pExpBar->Maximum = m_maxExp;
}

void PlayerMovement::OnFixedUpdate()
{
    m_pTransform->SetPosition(m_pTransform->position.x + m_movement.x * m_speed, m_pTransform->position.y + m_movement.y * m_speed);
    m_movement = sf::Vector2f(0, 0);
    m_pCamera->GetTransform()->position = m_pTransform->position - sf::Vector2f(m_rw->GetWindowWidth() / 2, m_rw->GetWindowHeight() / 2);
}

void PlayerMovement::OnCollisionEnter(Entity* other)
{
    if (other->IsTag(Entity::Tag::XP))
    {
        m_experience += other->GetComponent<Experience>()->GetValue();
        if (m_experience >= m_maxExp)
            LevelUp();
    }
}

void PlayerMovement::OnUpdate()
{
    m_pHealthBar->Progress = m_hp;
    m_pHealthBar->Maximum = m_maxHp;

    m_pExpBar->Progress = m_experience;
    m_time += m_pGameManager->GetTime()->GetDeltaTime();

    if (m_experience >= m_maxExp)
    {
        LevelUp();
    }
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
    //attackRect->GetTransform()->SetScale(sf::Vector2f(2, 5));
    ObjectFactory::CreateComponent<AABBCollider>(attackRect);
    ObjectFactory::AttachScript<Sword>(attackRect, m_direction);
    Animator* pAnim = ObjectFactory::CreateComponent<Animator>(attackRect, Resources::instance().VFX_SLASH, 0.1f);
    sf::Vector2f ownerPos = m_pOwner->GetTransform()->position;
    sf::Vector2f futurePos = ownerPos + m_direction * m_attackDistance;
    float rotation = atan2(m_direction.y, m_direction.x);
    attackRect->GetTransform()->rotation = sf::radians(rotation);
    attackRect->GetTransform()->position = futurePos;
}

void PlayerMovement::LevelUp()
{
    m_experience -= m_maxExp;
    m_maxExp += 5;
    m_pExpBar->Maximum = m_maxExp;
    
}

void PlayerMovement::TakeDamage(float damage)
{
    m_hp -= damage;
}
