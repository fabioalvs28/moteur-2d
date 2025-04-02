#pragma once
#include "scripts/Script.h"

class GameManager;
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
    Weapon(sf::Vector2f direction);

    void SetWeaponType(WEAPON_TYPES);
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
    virtual void OnAttack() = 0;

protected:
    float m_time = 0.0f;
    float m_velocity;
    float m_lifeSpan;

    sf::Vector2f m_direction;
    WEAPON_TYPES m_weaponType;
    GameManager* m_pGameManager;

};
