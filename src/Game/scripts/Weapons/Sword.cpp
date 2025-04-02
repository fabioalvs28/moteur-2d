#include "pch.h"
#include "Sword.h"
#include "Managers/GameManager.h"
#include "Transform.h"


Sword::Sword(sf::Vector2f direction)
{
    m_direction = direction;
}

void Sword::OnStart()
{
    m_time = 0.0f;
    m_pGameManager = Engine::GetGameManager();
    m_velocity = 0.0f;
    m_lifeSpan = 5.0f;
    m_weaponType = TYPE_SWORD;
}

void Sword::OnFixedUpdate()
{
    TRANSFORM* ownerTransform = m_pOwner->GetTransform();
    m_pOwner->GetTransform()->SetPosition(ownerTransform->position.x + m_direction.x * m_velocity, ownerTransform->position.y + m_direction.y * m_velocity);
}

void Sword::OnUpdate()
{
    m_time += m_pGameManager->GetTime()->GetDeltaTime();
    if (m_time >= m_lifeSpan)
    {
        m_time -= m_lifeSpan;
        m_pOwner->Destroy();
    }
}

void Sword::OnAttack()
{
    
}
