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
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}

protected:
    float m_velocity;
    float m_range;
    float m_distanceToPlayer;
    float m_lifeSpan;
    WEAPON_TYPES m_weaponType;

};
