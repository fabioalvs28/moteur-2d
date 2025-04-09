#include "pch.h"
#include "Experience.h"

#include "Transform.h"

sf::Vector2f Normalize(sf::Vector2f vec) {
    float mag = sqrt(vec.x * vec.x + vec.y * vec.y);
    float x = vec.x / mag;
    float y = vec.y / mag;
    return sf::Vector2f(x, y);
}

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
    m_value = 100;
}

void Experience::OnUpdate()
{
}

int Experience::GetValue()
{
    return m_value;
}
