#include "pch.h"
#include "Experience.h"

#include "Transform.h"

sf::Vector2f Normalize(sf::Vector2f vec) {
    float mag = sqrt(vec.x * vec.x + vec.y * vec.y);
    float x = vec.x / mag;
    float y = vec.y / mag;
    return sf::Vector2f(x, y);
}

void Experience::OnTriggerStay(Entity* other)
{
    if (other->IsTag(Entity::Tag::PLAYER))
    {
        sf::Vector2f position = m_pOwner->GetTransform()->position;
        while (position != other->GetTransform()->position)
        {
            sf::Vector2f direction = position - other->GetTransform()->position;
            position = position + Normalize(direction);
        }
    }
}

void Experience::OnStart()
{
    m_value = 1;
}

int Experience::GetValue()
{
    return m_value;
}
