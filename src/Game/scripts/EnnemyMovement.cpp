#include "pch.h"
#include "EnnemyMovement.h"

#include "Transform.h"

EnnemyMovement::EnnemyMovement(Entity* player)
{
    mpPlayer = player;
}

void EnnemyMovement::OnStart()
{
    mpTransform = m_pOwner->GetTransform();
}

void EnnemyMovement::OnFixedUpdate()
{
    float speed = 50.0f;
    mpTransform->position += movement * speed * Engine::GetDeltaTime();
    movement = sf::Vector2f(0, 0);
}

void EnnemyMovement::OnUpdate()
{
    sf::Vector2f direction = mpPlayer->GetTransform()->position - mpTransform->position;

    movement += direction.normalized();  // NOLINT(clang-diagnostic-undefined-func-template)
}

