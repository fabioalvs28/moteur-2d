#pragma once

#include "Component.h"

struct PhysicsMaterial : public Component
{
    static constexpr int BITMASK = 1 << 4;
    
    PhysicsMaterial(Entity* entity);
    void SetNewMaterial(const PhysicsMaterial* material);
    int GetBitmask() override;
    void Serialize(json& json) override;
    void Deserialize(json& json) override;
    float mElasticity = 0.1f;
    
    //Not Used
    float mStaticFriction = 0.6f;
    float mDynamicFriction = 0.6f;
};