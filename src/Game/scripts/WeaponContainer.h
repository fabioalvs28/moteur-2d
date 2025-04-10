#pragma once
#include "scripts/script.h"

class WeaponContainer : public IScript
{
public:
    WeaponContainer() = default;

    void OnStart() override;
    void AddWeapons(Sprite* nWeaponsIcon);
    void AddBuffs(Sprite* nBuffsIcon);
private:
    std::vector<Entity*> m_WeaponsIconsList;
    std::vector<Entity*> m_BuffsIconsList;
    
};
