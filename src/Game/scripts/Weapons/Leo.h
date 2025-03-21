#pragma once
#include "Weapon.h"

class Leo : public Weapon
{
public:

    Leo() = default;
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
};
