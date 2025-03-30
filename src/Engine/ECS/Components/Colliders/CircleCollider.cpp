#include "pch.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Entity* entity, int radius) : Collider2D(entity)
{
    mColliderType = ColliderType::CIRCLE;
    mRadius = radius;
    mpShape = new sf::CircleShape(radius);
    mpShape->setFillColor(sf::Color::Green);
}

void CircleCollider::Serialize(json& json)
{
    json["Center"] = {{ "x", mCenter.x}, { "y", mCenter.y}};
    json["ColliderType"] = ColliderTypeToString(this->GetColliderType());
    json["IsTrigger"] = this->IsTrigger();
    json["IsStatic"] = this->IsStatic();
    json["Radius"] = this->GetRadius();
}

int CircleCollider::GetBitmask()
{
    return BITMASK;
}
    
