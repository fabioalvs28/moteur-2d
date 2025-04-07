#include "pch.h"
#include "EnnemyMovement.h"

#include "Transform.h"


void EnnemyMovement::OnStart()
{
    mpTransform = owner->GetTransform();
    mpPlayerTransform = Engine::GetEntityByName("player")->GetTransform();;
}

void EnnemyMovement::OnFixedUpdate()
{
    float speed = 50.0f;
    mpTransform->position += movement * speed * Engine::GetDeltaTime();
    movement = sf::Vector2f(0, 0);
}

void EnnemyMovement::OnUpdate()
{
    sf::Vector2f direction = mpPlayerTransform->position - mpTransform->position;

    if(direction.x != 0 || direction.y != 0)
        movement += direction.normalized();  // NOLINT(clang-diagnostic-undefined-func-template)
}

