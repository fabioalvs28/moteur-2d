#include "pch.h"
#include "AABBCollider.h"

AABBCollider::AABBCollider(Entity* entity, float xMin, float yMin, float xMax, float yMax) : Collider2D(entity)
{
    mColliderType = ColliderType::AABB;
    mXMax = xMax;
    mYMax = yMax;
    mXMin = xMin;
    mYMin = yMin;
    mpShape = new sf::RectangleShape(sf::Vector2f(mXMax, mYMax));
    mpShape->setFillColor(sf::Color::Green);
    
}

void AABBCollider::Serialize(json& json)
{
    json["Center"] = {{ "x", mCenter.x}, { "y", mCenter.y}};
    json["ColliderType"] = ColliderTypeToString(this->GetColliderType());
    json["IsTrigger"] = this->IsTrigger();
    json["IsStatic"] = this->IsStatic();
    json["Min"] = {{ "x", mXMin}, { "y", mYMin}};
    json["Max"] = {{ "x", mXMax}, { "y", mYMax}};
}

int AABBCollider::GetBitmask()
{
    return BITMASK;
}
