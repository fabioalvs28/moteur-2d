#include "pch.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Entity* entity, float radius) : Collider2D(entity)
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

void CircleCollider::Deserialize(json& json)
{
    this->mCenter.x = json["Center"]["x"];
    this->mCenter.y = json["Center"]["y"];
    this->mColliderType = StringToColliderType(json["ColliderType"]);
    this->mIsStatic = json["IsStatic"];
    this->mIsTrigger = json["IsTrigger"];
    this->mRadius = json["Radius"];
}
