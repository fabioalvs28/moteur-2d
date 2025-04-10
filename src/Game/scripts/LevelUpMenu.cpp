#include "pch.h"
#include "LevelUpMenu.h"

#include "ObjectFactory.h"
#include "PlayerAttack.h"
#include "Weapons/Sword.h"
#include <algorithm>
#include <random>

#include "ECS/Components/ui/Button.h"
#include "Managers/GameManager.h"

LevelUpMenu::LevelUpMenu()
{
    Weapons = {
        {WEAPONS::SWORD, new WeaponInformations {
            WEAPON,
            (unsigned int)WEAPONS::SWORD,
            "Sword",
            "Basic sharp blade",
            "Sharpened blade: +10 dmg",
            Resources::instance().DEFAULT_SPRITE,
            "Sword",
            1,
            nullptr
            
        }},
        {WEAPONS::BOW, new WeaponInformations{
            WEAPON,
            (unsigned int)WEAPONS::BOW,
            "Bow",
            "Super BOWOWOWO",
            "MORE FIRE RATE",
            Resources::instance().DEFAULT_SPRITE,
            "Bow",
            1,
            nullptr
        }},
        {WEAPONS::LASER, new WeaponInformations {
            WEAPON,
            (unsigned int)WEAPONS::LASER,
            "Laser",
            "Succeseur de la Spear-Uline",
            "PLUS GROS",
            Resources::instance().DEFAULT_SPRITE,
            "Laser",
            1,
            nullptr
        }},
        {WEAPONS::FABIOJR, new WeaponInformations {
            WEAPON,
            (unsigned int)WEAPONS::FABIOJR,
            "Fabio Jr",
            "Moche",
            "Rien du tout il est guez",
            Resources::instance().DEFAULT_SPRITE,
            "FabioJr",
            1,
            nullptr
        }},
        {WEAPONS::BOMB, new WeaponInformations {
            WEAPON,
            (unsigned int)WEAPONS::BOMB,
            "Bombe",
            "Bomba",
            "PLUS GROSSE BOMBE",
            Resources::instance().DEFAULT_SPRITE,
            "Bomb",
            1,
            nullptr
        }},
        {WEAPONS::BOOMERANG, new WeaponInformations {
            WEAPON,
            (unsigned int)WEAPONS::BOOMERANG,
            "Boomerang",
            "ça s'en va et ça revient",
            "PLUS DE BOOMERANG",
            Resources::instance().DEFAULT_SPRITE,
            "Boomerang",
            1,
            nullptr
        }}
    };

    for (auto& pair : Weapons)
        m_WeaponList.push_back(pair.second);
}

LevelUpMenu::~LevelUpMenu()
{
    for (auto& pair : Weapons)
        delete pair.second;
}

void LevelUpMenu::OnStart()
{
    Player = Engine::GetEntityByName("player");

    m_button1 = ObjectFactory::CreateEntity<Entity>(2);
    m_button2 = ObjectFactory::CreateEntity<Entity>(2);
    m_button3 = ObjectFactory::CreateEntity<Entity>(2);

    
    ObjectFactory::CreateComponent<Button>(m_button1,Resources::instance().BAR_EXP, sf::Vector2f{ 500, 300 },sf::Vector2f(1,1), 50, 50,[this]()
    {
        HandleWeaponChoice(0);
    }, [this](){});
    ObjectFactory::CreateComponent<Text>(
       m_button1,
       Resources::instance().DEFAULT_FONT,
       20,
       "",
       sf::Vector2f(300.f, 10.f + (300))
    );
    ObjectFactory::CreateComponent<Button>(m_button2,Resources::instance().BAR_EXP, sf::Vector2f{ 500, 500 }, sf::Vector2f(1, 1), 50,50,[this]()
    {
        HandleWeaponChoice(1);
    }, [this](){});
    ObjectFactory::CreateComponent<Text>(
       m_button2,
       Resources::instance().DEFAULT_FONT,
       20,
       "",
       sf::Vector2f(300.f, 10.f + (500))
    );
    ObjectFactory::CreateComponent<Button>(m_button3,Resources::instance().BAR_EXP, sf::Vector2f{ 500, 700 }, sf::Vector2f(1, 1), 50,50,[this]()
    {
        HandleWeaponChoice(2);
    }, [this](){});
    ObjectFactory::CreateComponent<Text>(
       m_button3,
       Resources::instance().DEFAULT_FONT,
       20,
       "",
       sf::Vector2f(300.f, 10.f + (700))
    );
    m_button1->SetEnabled(false);
    m_button2->SetEnabled(false);
    m_button3->SetEnabled(false);
}

void LevelUpMenu::OnUpdate() {}

void LevelUpMenu::GenerateSelectionPool()
{
    m_WeaponChoice.clear();
    srand(time(NULL));

    while(m_WeaponChoice.size() < 3)
    {
        int randomNum = rand() % GetWeaponPool().size();
        WeaponInformations* weapon = m_WeaponList[randomNum];

        if (std::find(m_WeaponChoice.begin(), m_WeaponChoice.end(), weapon) == m_WeaponChoice.end())
        {
            m_WeaponChoice.push_back(weapon);
        }
    }

}

void LevelUpMenu::OnSpawn()
{
    GenerateSelectionPool();

    //m_background->SetEnabled(true);
    m_button1->SetEnabled(true);
    m_button2->SetEnabled(true);
    m_button3->SetEnabled(true);

    // Ajout du texte à chaque bouton
    std::vector<Entity*> buttons = { m_button1, m_button2, m_button3 };
    for (int i = 0; i < 3; ++i)
    {
        if (i >= m_WeaponChoice.size()) break;

        WeaponInformations* info = m_WeaponChoice[i];
        std::string displayText = info->name + "\n" + (info->level == 1 ? info->descriptionText : info->upgradeText);

        if(!buttons[i]->HasComponent<Text>())
        {
            ObjectFactory::CreateComponent<Text>(
               buttons[i],
               Resources::instance().DEFAULT_FONT,
               20,
               displayText,
               sf::Vector2f(300.f, 10.f + (300 - (i * 100.0f)))
            );
        }
        else
        {
            buttons[i]->GetComponent<Text>()->WriteText->setString(displayText);
        }


    }
}

void LevelUpMenu::OnClose()
{
    m_WeaponChoice.clear();
    //m_background->SetEnabled(false);
    m_button1->SetEnabled(false);
    m_button2->SetEnabled(false);
    m_button3->SetEnabled(false);

    
    Engine::GetGameManager()->GetTime()->Resume();
}

bool LevelUpMenu::HandleWeaponChoice(int index)
{
    WeaponInformations* selected = m_WeaponChoice[index];
    
    if (selected->level == 1)
    {
        if(selected->name == "Sword")
        {
            selected->weaponScript = Engine::GetEntityByName("player")->GetScript<Sword>();
        }
        else
        {
            IScript* script = Engine::GetScriptManager()->CreateScriptByName(selected->weaponScriptName);
            ObjectFactory::AddScript(script, Player);
            selected->weaponScript = static_cast<Weapon*>(script);
            Player->GetScript<PlayerAttack>()->AddWeapon(selected->weaponScript);
        }

    }
    else if (selected->weaponScript)
    {
        selected->weaponScript->Upgrade();
    }

    selected->level++;
    OnClose();
    return true;
}