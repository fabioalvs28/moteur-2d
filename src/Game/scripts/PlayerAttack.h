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

    void AddBuff(Buffs* nBuffs) { m_BuffList.push_back(nBuffs); }
    std::vector<Buffs*>& GetBuffsList() { return m_BuffList; }

    
private:
    std::vector<Weapon*> m_WeaponsList;
    std::vector<Buffs*> m_BuffList;
};
