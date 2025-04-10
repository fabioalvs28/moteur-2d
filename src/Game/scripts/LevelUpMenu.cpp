#include "pch.h"
#include "LevelUpMenu.h"

#include "ObjectFactory.h"
#include "PlayerAttack.h"
#include "Weapons/Sword.h"
#include <algorithm>
#include <random>

#include "PlayerMovement.h"
#include "WeaponContainer.h"
#include "ECS/Components/ui/Button.h"
#include "ECS/Components/ui/Image.h"
#include "Managers/GameManager.h"

LevelUpMenu::~LevelUpMenu()
{
}

void LevelUpMenu::OnStart()
{
      m_ItemsList = {
    new ItemsInformations {
        WEAPON,
        (unsigned int)WEAPONS::SWORD,
        "Sword",
        "Arme qui coupe",
        "Tu fais plus mal...\net c'est tout",
        Resources::instance().SWORD,
        "Sword",
        2,
        nullptr
    },
    new ItemsInformations {
        WEAPON,
        (unsigned int)WEAPONS::LASER,
        "Laser",
        "Succeseur de la \nSpear-Uline",
        "PLUS GROS",
        Resources::instance().LASER,
        "Laser",
        1,
        nullptr
    },
    new ItemsInformations {
        WEAPON,
        (unsigned int)WEAPONS::FABIOJR,
        "Fabio Jr",
        "Personne ne l'aime",
        "Plus de Fabio\nmalheureusement...",
        Resources::instance().FABIOJR,
        "FabioJr",
        1,
        nullptr
    },
    new ItemsInformations {
        WEAPON,
        (unsigned int)WEAPONS::BOMB,
        "Bombe",
        "C'est de la bombe",
        "Plus grosse bombe",
        Resources::instance().BOMB,
        "Bomb",
        1,
        nullptr
    },
    new ItemsInformations {
        WEAPON,
        (unsigned int)WEAPONS::BOOMERANG,
        "Boomerang",
        "Tourne et retourne",
        "J'ai plus d'inspiration",
        Resources::instance().BOOMERANG,
        "Boomerang",
        1,
        nullptr
    },
    new ItemsInformations {
        WEAPON,
        (unsigned int)WEAPONS::DEO,
        "Deodorant",
        "Meilleur arme \ncontre les techs",
        "Le deo traverse une\nplus grande distance",
        Resources::instance().DEO,
        "BodyCount",
        1,
        nullptr
    },
    new ItemsInformations {
        BUFFS,
        (unsigned int)BUFFS::DEV,
        "Dev++",
        "J'adore DEV++ !\nDegats +10%",
        "+10% de degats\nVive Dev++ !",
        Resources::instance().DEV,
        "",
        1,
        nullptr
    },
    new ItemsInformations {
        BUFFS,
        (unsigned int)BUFFS::KONG,
        "Kong",
        "Pour finir le moteur !\nVitesse +10%",
        "+10% de vitesse \n(et de rythme cardiaque)",
        Resources::instance().KONG,
        "",
        1,
        nullptr
    },
    new ItemsInformations {
        BUFFS,
        (unsigned int)BUFFS::KINDER,
        "Kinder Bueno",
        "5 euros aux distribs\nDonne 25 HP",
        "Moins d'argent mais\nrends 25PV !",
        Resources::instance().KINDER,
        "",
        1,
        nullptr
    },
    new ItemsInformations {
        BUFFS,
        (unsigned int)BUFFS::GC_ENGINE,
        "Morceau du GC ENGINE",
        "L'objectif est en vue!\nVitesse des armes +10%",
        "GIT FORCE PUSH\nVitesse des armes +10%",
        Resources::instance().GC_ENGINE,
        "",
        1,
        nullptr
    },
    new ItemsInformations {
        BUFFS,
        (unsigned int)BUFFS::BODYCOUNT,
        "Bodycount",
        "Quel aura meurtriere !\nDelai des armes -10%",
        "Aura Farming\nDelai des armes -10%",
        Resources::instance().BODYCOUNT,
        "",
        1,
        nullptr
    },
    new ItemsInformations {
        BUFFS,
        (unsigned int)BUFFS::CARAMEL_BISCUIT,
        "Caramel Biscuit",
        "A la vie, a la mort\nVie maximale +10%",
        "Vie max +10%\nGlycemie +10%",
        Resources::instance().CARAMEL_BISCUIT,
        "",
        1,
        nullptr
    }
};
    
    Player = Engine::GetEntityByName("player");

    m_button1 = ObjectFactory::CreateEntity<Entity>(2);
    m_button2 = ObjectFactory::CreateEntity<Entity>(2);
    m_button3 = ObjectFactory::CreateEntity<Entity>(2);

    
    ObjectFactory::CreateComponent<Button>(m_button1,Resources::instance().KONG_BUTTON, sf::Vector2f{ (Engine::GetRenderWindow()->getSize().x * 0.5f) - (Resources::instance().BUTTON_KONG_TEXTURE->getSize().x * 0.5f) , 200 }, Resources::instance().BUTTON_KONG_TEXTURE->getSize().x, Resources::instance().BUTTON_KONG_TEXTURE->getSize().y,[this]()
    {
        HandleChoice(0);
    }, [this](){});
    ObjectFactory::CreateComponent<Text>(
       m_button1,
       Resources::instance().DEFAULT_FONT,
       20,
       "",
       sf::Vector2f(710.f, (225))
    );
    ObjectFactory::CreateComponent<Button>(m_button2,Resources::instance().KONG_BUTTON, sf::Vector2f{ (Engine::GetRenderWindow()->getSize().x * 0.5f) - (Resources::instance().BUTTON_KONG_TEXTURE->getSize().x * 0.5f) , 400 }, Resources::instance().BUTTON_KONG_TEXTURE->getSize().x, Resources::instance().BUTTON_KONG_TEXTURE->getSize().y,[this]()
    {
        HandleChoice(1);
    }, [this](){});
    ObjectFactory::CreateComponent<Text>(
       m_button2,
       Resources::instance().DEFAULT_FONT,
       20,
       "",
       sf::Vector2f(710.f, (425))
    );
    ObjectFactory::CreateComponent<Button>(m_button3,Resources::instance().KONG_BUTTON, sf::Vector2f{ (Engine::GetRenderWindow()->getSize().x * 0.5f) - (Resources::instance().BUTTON_KONG_TEXTURE->getSize().x * 0.5f) , 600 }, Resources::instance().BUTTON_KONG_TEXTURE->getSize().x, Resources::instance().BUTTON_KONG_TEXTURE->getSize().y,[this]()
    {
        HandleChoice(2);
    }, [this](){});
    ObjectFactory::CreateComponent<Text>(
       m_button3,
       Resources::instance().DEFAULT_FONT,
       20,
       "",
       sf::Vector2f(710.f, (625))
    );
    ObjectFactory::CreateComponent<Image>(m_button1, nullptr, sf::Vector2f(880.0f, 260.0f));
    ObjectFactory::CreateComponent<Image>(m_button2, nullptr, sf::Vector2f(880.0f, 460.0f));
    ObjectFactory::CreateComponent<Image>(m_button3, nullptr, sf::Vector2f(880.0f, 660.0f));
    m_button1->SetEnabled(false);
    m_button2->SetEnabled(false);
    m_button3->SetEnabled(false);
}

void LevelUpMenu::OnUpdate() {}

void LevelUpMenu::GenerateSelectionPool()
{
    m_ItemsChoice.clear();
    srand(time(NULL));

    while(m_ItemsChoice.size() < 3)
    {
        int randomNum = rand() % GetWeaponPool().size();
        ItemsInformations* weapon = m_ItemsList[randomNum];

        if (std::find(m_ItemsChoice.begin(), m_ItemsChoice.end(), weapon) == m_ItemsChoice.end())
        {
            m_ItemsChoice.push_back(weapon);
        }
    }

}

void LevelUpMenu::OnSpawn()
{
    GenerateSelectionPool();

    m_button1->SetEnabled(true);
    m_button2->SetEnabled(true);
    m_button3->SetEnabled(true);

    // Ajout du texte à chaque bouton
    std::vector<Entity*> buttons = { m_button1, m_button2, m_button3 };
    for (int i = 0; i < 3; ++i)
    {
        ItemsInformations* info = m_ItemsChoice[i];
        std::string displayText = info->name + "\n\n" + (info->level == 1 ? info->descriptionText : info->upgradeText);

        buttons[i]->GetComponent<Text>()->WriteText->setString(displayText);
        buttons[i]->GetComponent<Image>()->UIImage = m_ItemsChoice[i]->WeaponSprite;
        
    }
}

void LevelUpMenu::OnClose()
{
    m_ItemsChoice.clear();
    m_button1->SetEnabled(false);
    m_button2->SetEnabled(false);
    m_button3->SetEnabled(false);

    
    Engine::GetGameManager()->GetTime()->Resume();
}

bool LevelUpMenu::HandleChoice(int index)
{
    ItemsInformations* selected = m_ItemsChoice[index];

    if(selected->type == WEAPON)
    {
        if (selected->level == 1)
        {
            IScript* script = Engine::GetScriptManager()->CreateScriptByName(selected->weaponScriptName);
            ObjectFactory::AddScript(script, Player);
            selected->weaponScript = static_cast<Weapon*>(script);
            Player->GetScript<PlayerAttack>()->AddWeapon(selected->weaponScript);
        }
        else if (selected->weaponScript)
        {
            if(selected->name == "Sword")
            {
                selected->weaponScript = Engine::GetEntityByName("player")->GetScript<Sword>();
            }
            selected->weaponScript->Upgrade();
        }

        Player->GetScript<WeaponContainer>()->AddWeapons(m_ItemsChoice[index]->WeaponSprite);
    }
    else
    {
        //MOCHE MAIS PAS LE TEMPS :(
        switch(selected->id)
        {
        case (unsigned int)BUFFS::DEV :
            {
                for(Weapon* weapon : Player->GetScript<PlayerAttack>()->GetWeaponList())
                {
                    weapon->m_damages *= 1.1f;
                }
                break;
            }
        case (unsigned int)BUFFS::KONG :
            {
                Player->GetScript<PlayerMovement>()->m_speed *= 1.1f;
                break;
            }
        case (unsigned int)BUFFS::KINDER :
            {
                Player->GetScript<PlayerMovement>()->m_hp += 25.0f;
                break;
            }
        case (unsigned int)BUFFS::GC_ENGINE :
            {
                for(Weapon* weapon : Player->GetScript<PlayerAttack>()->GetWeaponList())
                {
                    weapon->m_velocity *= 1.1f;
                }
                break;
            }
        case (unsigned int)BUFFS::BODYCOUNT :
            {
                for(Weapon* weapon : Player->GetScript<PlayerAttack>()->GetWeaponList())
                {
                    weapon->m_attackDelay *= 0.9f;
                }
                break;
            }
        case (unsigned int)BUFFS::CARAMEL_BISCUIT :
            {
                Player->GetScript<PlayerMovement>()->m_hp *= 1.1f;
                break;
            }
        }
        Player->GetScript<WeaponContainer>()->AddBuffs(m_ItemsChoice[index]->WeaponSprite);
    }
    

    selected->level++;
    OnClose();
    return true;
}