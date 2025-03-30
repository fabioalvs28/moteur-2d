#pragma once
#include "ECS/Components/Collider2D.h"

class CircleCollider : public Collider2D
{
public:
    static constexpr int BITMASK = 1 << 9;

    CircleCollider(Entity* entity, int radius);
    void SetRadius(float radius) { mRadius = radius; }
    float GetRadius() const { return mRadius; }
    void Serialize(json& json) override;
    int GetBitmask() override;

private:
    float mRadius;
};
