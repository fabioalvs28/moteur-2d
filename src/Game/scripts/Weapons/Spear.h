#pragma once
#include "Weapon.h"

class Spear : public Weapon
{
public:

    Spear() = default;
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
};
