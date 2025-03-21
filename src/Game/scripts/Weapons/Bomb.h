#pragma once
#include "Weapon.h"

class Bomb : public Weapon
{
public:

    Bomb() = default;
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
};
