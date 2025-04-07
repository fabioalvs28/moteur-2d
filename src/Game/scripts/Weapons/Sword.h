#pragma once
#include "Weapon.h"

class Sword : public Weapon
{
public:

    Sword() = default;
    Sword(sf::Vector2f direction);

    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override {}
    void OnAttack() override;
    void OnCollisionEnter(Entity* other) override;
};
