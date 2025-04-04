#include "pch.h"
#include "EnnemyMovement.h"

#include "Transform.h"

EnemyMovement::EnemyMovement(Entity* player)
{
    m_pPlayer = player;
}

void EnemyMovement::OnStart()
{
    m_pTransform = m_pOwner->GetTransform();
}

void EnemyMovement::OnFixedUpdate()
{
    float speed = 50.0f;
    m_pTransform->position += m_movement * speed * Engine::GetDeltaTime();
    m_movement = sf::Vector2f(0, 0);
}

void EnemyMovement::OnUpdate()
{
    sf::Vector2f direction = m_pPlayer->GetTransform()->position - m_pTransform->position;

    m_movement += direction.normalized();  // NOLINT(clang-diagnostic-undefined-func-template)
}

