#pragma once
#include "scripts/Script.h"

class WeaponAttack : public IScript
{
public:
    WeaponAttack() = default;
    WeaponAttack(float damage, float attackDistance, float velocity, sf::Vector2f direction);
    void OnStart() override;
    void OnUpdate() override;
    void OnFixedUpdate() override;
    void OnTriggerEnter(Entity* other) override;
    

private:
    float m_damage;
    float m_attackDistance;
    float m_velocity;
    sf::Vector2f m_direction;
    TRANSFORM* mp_OwnerTransform;
    float m_lifeSpan;
    float m_time;
};
