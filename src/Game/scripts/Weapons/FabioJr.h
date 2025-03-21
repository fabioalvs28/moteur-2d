#pragma once
#include "Weapon.h"

class FabioJr : public Weapon
{
public:

    FabioJr() = default;
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
};
