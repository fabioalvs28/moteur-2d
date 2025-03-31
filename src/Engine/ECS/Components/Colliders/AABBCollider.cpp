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

void AABBCollider::Deserialize(json& json)
{
    this->mCenter.x = json["Center"]["x"];
    this->mCenter.y = json["Center"]["y"];
    this->mColliderType = StringToColliderType(json["ColliderType"]);
    this->mIsStatic = json["IsStatic"];
    this->mIsTrigger = json["IsTrigger"];
    this->mXMin = json["Min"]["x"];
    this->mYMin = json["Min"]["y"];
    this->mXMax = json["Max"]["x"];
    this->mYMax = json["Max"]["y"];
}


int AABBCollider::GetBitmask()
{
    return BITMASK;
}
