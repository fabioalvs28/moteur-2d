#pragma once
#include "ECS/Components/Collider2D.h"

class AABBCollider : public Collider2D
{
public:
    AABBCollider(Entity* entity, float xMin = 0.0f, float yMin = 0.0f, float xMax = 10.0f, float yMax = 10.0f);
    float GetMaxX() const { return mXMax; }
    float GetMaxY() const { return mYMax; }
    float GetMinX() const { return mXMin; }
    float GetMinY() const { return mYMin; }

    sf::Vector2f GetMin() { return { mXMin, mYMin }; }
    sf::Vector2f GetMax() { return { mXMax, mYMax }; }

    void Serialize(json& json) override;
    void Deserialize(json& json) override;
    static constexpr int BITMASK = 1 << 10;
    int GetBitmask() override;


protected:
    float mXMin;
    float mYMin;
    float mXMax;
    float mYMax;
    
};
