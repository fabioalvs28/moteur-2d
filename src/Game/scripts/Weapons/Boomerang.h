#pragma once
#include "Weapon.h"

class Boomerang : public Weapon
{
public:
    Boomerang() = default;
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
};
