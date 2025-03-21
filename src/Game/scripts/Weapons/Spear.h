#pragma once
#include "scripts/Script.h"

class Weapon : public IScript
{
public:
    enum WEAPON_TYPES
    {
        TYPE_SWORD, //Base Weapons
        TYPE_BOW,
        TYPE_SPEAR,

        TYPE_BOOMERANG, //In-Game Weapons
        TYPE_BOMB,
        TYPE_FABIOJR,
        TYPE_LEO,

        TYPECOUNT
    };

    Weapon() = default;

    virtual void SetWeaponType(WEAPON_TYPES);
    virtual void OnStart() override;
    virtual void OnFixedUpdate() override {};
    virtual void OnUpdate() override;
    virtual void OnDisable() override {};

private:
    float m_velocity;
    float m_range;
    float m_distanceToPlayer;
    float m_lifeSpan;
    WEAPON_TYPES m_weaponType;

};
