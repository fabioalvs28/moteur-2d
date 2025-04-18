#pragma once
#include "scripts/Script.h"

class LevelUpMenu;
class GameManager;
class Weapon : public IScript
{
public:
    enum WEAPON_TYPES
    {
        TYPE_SWORD, //Base Weapons
        TYPE_BOW,
        TYPE_LASER,

        TYPE_BOOMERANG, //In-Game Weapons
        TYPE_BOMB,
        TYPE_FABIOJR,
        TYPE_DEO,

        TYPECOUNT
    };

    Weapon() = default;
    Weapon(sf::Vector2f direction);

    void SetWeaponType(WEAPON_TYPES);
    void OnStart() override;
    void OnFixedUpdate() override {}
    void OnUpdate() override;
    void OnDisable() override {}
    void OnCollisionEnter(Entity* other) override {};
    virtual void OnAttack() = 0;
    virtual void Upgrade() {};

protected:
    float m_time;
    float m_velocity;
    float m_lifeSpan;
    float m_damages;
    float m_attackDistance;
    float m_attackDelay;
    int m_level;
    sf::Vector2f m_direction;
    WEAPON_TYPES m_weaponType;
    GameManager* m_pGameManager;

    friend LevelUpMenu;

};
