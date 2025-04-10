#pragma once
#include "Buffs/Buffs.h"
#include "scripts/Script.h"
#include "Weapons/Weapon.h"

class PlayerAttack : public IScript
{
public:
    void OnUpdate() override;

    void AddWeapon(Weapon* nWeapon) { m_WeaponsList.push_back(nWeapon); }
    std::vector<Weapon*>& GetWeaponList() { return m_WeaponsList;}
    
private:
    std::vector<Weapon*> m_WeaponsList;
};
