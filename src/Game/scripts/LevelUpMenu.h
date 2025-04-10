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
    LASER,
    DEO,

    WEAPONS_COUNT
};

enum class BUFFS : uint32_t
{
    KONG,
    CARAMEL_BISCUIT,
    GC_ENGINE,
    BODYCOUNT,
    KINDER,
    DEV,

    BUFFS_COUNT
    
};
enum ItemType : uint8_t
{
    WEAPON,
    BUFFS,

    COUNT_TYPE
};

struct ItemsInformations
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
    LevelUpMenu() = default;
    ~LevelUpMenu();

    void OnStart() override;
    void OnUpdate() override;

    void GenerateSelectionPool();
    void OnSpawn();
    void OnClose();
    bool HandleChoice(int index);

    std::vector<ItemsInformations*>& GetWeaponPool() { return m_ItemsList; }

private:
    Entity* m_button1 ;
    Entity* m_button2;
    Entity* m_button3;
    Entity* Player;

    std::vector<Entity*> TextContainer;
    std::vector<ItemsInformations*> m_ItemsList;
    std::vector<ItemsInformations*> m_ItemsChoice;
};

REGISTER_SCRIPT(LevelUpMenu)
