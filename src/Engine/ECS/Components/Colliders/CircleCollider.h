#pragma once
#include "ECS/Components/Collider2D.h"

class CircleCollider : public Collider2D
{
public:
    static constexpr int BITMASK = 1 << 9;

    CircleCollider(Entity* entity, int radius = 0.0f);
    void SetRadius(float radius) { mRadius = radius; }
    float GetRadius() const { return mRadius; }
    void Serialize(json& json) override;
    int GetBitmask() override;
    void Deserialize(json& json) override;

private:
    float mRadius;
};
