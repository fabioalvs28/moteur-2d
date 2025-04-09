#include "pch.h"
#include "Experience.h"

#include "Transform.h"
#include "scripts/PlayerMovement.h"

void Experience::OnTriggerEnter(Entity* other)
{
    if (other->IsTag(Entity::Tag::PLAYER))
    {
        if(position != other->GetTransform()->position)
        {
            sf::Vector2f direction = position - other->GetTransform()->position;
            if(direction.normalized() != sf::Vector2f(0.0f,0.0f))
                position = direction.normalized() + position;
        }
    }
}

void Experience::OnStart()
{
    position = m_pOwner->GetTransform()->position;
    m_value = rand() % 6 + 10;
    m_speed = 500.0f;
    m_distance = 10.0f;
}

void Experience::OnUpdate()
{
    sf::Vector2f pPlayerPos = Engine::GetEntityByName("player")->GetTransform()->position;
    sf::Vector2f pos = m_pOwner->GetTransform()->position;
    sf::Vector2f direction = pPlayerPos - pos;
    float distance = (pPlayerPos.x - pos.x) + (pPlayerPos.y - pPlayerPos.y);
    if (distance <= m_distance)
        m_pOwner->GetTransform()->position = m_pOwner->GetTransform()->position + direction.normalized() * Engine::GetDeltaTime() * m_speed;
}

int Experience::GetValue()
{
    return m_value;
}

void Experience::SetDistance(float distance)
{
    m_distance = distance;
}

void Experience::AddDistance(float add)
{
    m_distance += add;
}
