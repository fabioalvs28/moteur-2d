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
    float speed = 2500.0f;
    m_pTransform->SetPosition(m_pTransform->position + (m_movement * speed * Engine::GetDeltaTime()));
    m_movement = sf::Vector2f(0, 0);
}

void EnemyMovement::OnUpdate()
{
    sf::Vector2f distance = m_pTransform->position - m_pPlayerTransform->position;

    if(distance.length() >= sf::Vector2f(1000.0f, 1000.0f).length())
        m_pTransform->position = GenerateSpawnPosition();
    
    sf::Vector2f direction = m_pPlayerTransform->position - m_pTransform->position;

    if(direction.x != 0 || direction.y != 0)
        if(m_movement == sf::Vector2f(0.0f,0.0f))
            m_movement += direction.normalized();  // NOLINT(clang-diagnostic-undefined-func-template)
}

sf::Vector2f EnemyMovement::GenerateSpawnPosition()
{
    sf::Vector2f spawnPos;
    sf::Vector2f pos = m_pPlayerTransform->position;
    float camWidth = Engine::GetRenderWindow()->getSize().x;
    float camHeight = Engine::GetRenderWindow()->getSize().y;
    float buffer = 150.0f;
    int side = rand() % 4;

    switch(side)
    {
        case 0: // Gauche
            spawnPos.x = pos.x - camWidth / 2 - buffer;
            spawnPos.y = pos.y + (rand() % (int)camHeight) - camHeight / 2 + buffer;
            break;
        case 1: // Droite
            spawnPos.x = pos.x + camWidth / 2 + buffer;
            spawnPos.y = pos.y + (rand() % (int)camHeight) + camHeight / 2 + buffer;
            break;
        case 2: // Haut
            spawnPos.y = pos.y + camHeight / 2 + buffer;
            spawnPos.x = pos.x + (rand() % (int)camWidth) - camWidth / 2 + buffer;
            break;
        case 3: // Bas
            spawnPos.y = pos.y - camHeight / 2 - buffer;
            spawnPos.x = pos.x + (rand() % (int)camWidth) - camWidth / 2 + buffer;
            break;
    }

    return spawnPos;
}


