#pragma once
#include "Weapon.h"

class Sword : public Weapon
{
public:

    Sword() = default;
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
};
