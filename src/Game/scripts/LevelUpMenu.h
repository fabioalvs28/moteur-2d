#pragma once
#include "Resources.h"
#include "scripts/script.h"
#include "Engine/Scripts/ScriptRegistry.h"
#include "Weapons/Weapon.h"

struct WeaponInformations
{
    std::string name;
    std::string descriptionText;
    std::string upgradeText;
    Sprite* WeaponSprite;
    std::string weaponScriptName;
    int level;
    bool isEquipped;
    Weapon* weaponScript;
};

class LevelUpMenu : public IScript
{
public:
    void OnStart() override;
    void OnUpdate() override;

    void GenerateSelectionPool();
    void OnSpawn();
    std::vector<WeaponInformations*>& GetWeaponPool() { return m_WeaponList; }
    bool IsButtonClicked(Entity* other);
private:
    Entity* m_background;
    Entity* m_button1;
    Entity* m_button2;
    Entity* m_button3;
    Entity* Player;
    std::vector<WeaponInformations*> m_WeaponList;
    std::vector<WeaponInformations*> m_WeaponChoice;
};

REGISTER_SCRIPT(LevelUpMenu)

