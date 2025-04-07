#include "pch.h"
#include "EnnemyMovement.h"

#include "Transform.h"


void EnemyMovement::OnStart()
{
    m_pTransform = m_pOwner->GetTransform();
    m_pPlayerTransform = Engine::GetEntityByName("player")->GetTransform();
}

void EnemyMovement::OnFixedUpdate()
{
    float speed = 50.0f;
    m_pTransform->position += m_movement * speed * Engine::GetDeltaTime();
    m_movement = sf::Vector2f(0, 0);
}

void EnemyMovement::OnUpdate()
{
    sf::Vector2f direction = m_pPlayerTransform->position - m_pTransform->position;

    if(direction.x != 0 || direction.y != 0)
        m_movement += direction.normalized();  // NOLINT(clang-diagnostic-undefined-func-template)
}

