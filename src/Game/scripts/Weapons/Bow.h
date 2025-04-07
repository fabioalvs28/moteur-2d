#pragma once
#include "Weapon.h"

class Bow : public Weapon
{
public:

    Bow() = default;
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
};
