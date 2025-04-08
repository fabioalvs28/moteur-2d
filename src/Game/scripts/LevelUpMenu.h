#pragma once
#include "Resources.h"
#include "ECS/Components/ui/Text.h"
#include "scripts/script.h"
#include "Engine/Scripts/ScriptRegistry.h"
#include "Weapons/Weapon.h"

enum class WEAPONS : uint32_t
{
    SWORD,
    FABIOJR,
    BOMB,
    BOOMERANG,
    BOW,
    SPEAR,

    WEAPONS_COUNT
};

enum ItemType : uint8_t
{
    WEAPON,
    BUFFS,

    COUNT_TYPE
};

struct WeaponInformations
{
    ItemType type;
    unsigned int id;
    std::string name;
    std::string descriptionText;
    std::string upgradeText;
    Sprite* WeaponSprite;
    std::string weaponScriptName;
    int level = 1;
    Weapon* weaponScript = nullptr;
};

class LevelUpMenu : public IScript
{
public:
    LevelUpMenu();
    ~LevelUpMenu();

    void OnStart() override;
    void OnUpdate() override;

    void GenerateSelectionPool();
    void OnSpawn();
    void OnClose();
    bool HandleWeaponChoice(int index);

    std::vector<WeaponInformations*>& GetWeaponPool() { return m_WeaponList; }

private:
    Entity* m_background;
    Entity* m_button1 ;
    Entity* m_button2;
    Entity* m_button3;
    Entity* Player;

    std::vector<Entity*> TextContainer;
    std::map<WEAPONS, WeaponInformations*> Weapons;
    std::vector<WeaponInformations*> m_WeaponList;
    std::vector<WeaponInformations*> m_WeaponChoice;
};

REGISTER_SCRIPT(LevelUpMenu)
