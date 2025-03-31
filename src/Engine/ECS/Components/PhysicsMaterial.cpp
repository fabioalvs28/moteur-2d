#include "pch.h"
#include "PhysicsMaterial.h"

PhysicsMaterial::PhysicsMaterial(Entity* entity) : Component(entity)
{
}

void PhysicsMaterial::SetNewMaterial(const PhysicsMaterial* material)
{
    this->mElasticity = material->mElasticity;
    this->mDynamicFriction = material->mDynamicFriction;
    this->mStaticFriction = material->mStaticFriction;
}

int PhysicsMaterial::GetBitmask()
{
    return BITMASK;
}

void PhysicsMaterial::Serialize(json& json)
{
    json["Elasticity"] = this->mElasticity;
    json["DynamicFriction"] = this->mDynamicFriction;
    json["StaticFriction"] = this->mStaticFriction;
}

void PhysicsMaterial::Deserialize(json& json)
{
    this->mElasticity = json["Elasticity"];
    this->mDynamicFriction = json["DynamicFriction"] ;
    this->mStaticFriction = json["StaticFriction"];

}
