#include "pch.h"
#include "LevelUpMenu.h"

#include "ObjectFactory.h"
#include "PlayerAttack.h"
#include "Weapons/Sword.h"

void LevelUpMenu::OnStart()
{
    Player = Engine::GetEntityByName("player");
    
    
    WeaponInformations Sword =
        {
            "Sword",
            "A Sword that's swording",
            "More Damage",
            Resources::instance().DEFAULT_SPRITE,
            "Sword",
            1,
            false,
            nullptr
        };
}

void LevelUpMenu::OnUpdate()
{
    
}

void LevelUpMenu::GenerateSelectionPool()
{
    for(int i = 0; i < 3; i++)
    {
        int randomNum = rand() % GetWeaponPool().size();

        if(m_WeaponList[randomNum]->level <= 7)
        {
            if(m_WeaponList[randomNum]->weaponScript == nullptr)
            {
                IScript* t = Engine::GetScriptManager()->CreateScriptByName(m_WeaponList[randomNum]->weaponScriptName);
                ObjectFactory::AddScript(t, Player);
            }

            m_WeaponChoice.push_back(m_WeaponList[randomNum]);
        }
    }

}

void LevelUpMenu::OnSpawn()
{
    GenerateSelectionPool();

    //TODO : ASPECT GRAPHIQUE
}

bool LevelUpMenu::IsButtonClicked(Entity* other)
{
    switch (other)
    {
        case(other == m_button1) :
        {
                WeaponInformations* info = m_WeaponChoice[0];
                if(info->level == 1)
                {
                    Player->GetScript<PlayerAttack>()->AddWeapon(info->weaponScript);
                }
                else
                {
                    info->weaponScript->Upgrade();
                    info->level++;
                }
                break;
        }
        case(other == m_button2) :
        {
                WeaponInformations* info = m_WeaponChoice[1];
                if(info->level == 1)
                {
                    Player->GetScript<PlayerAttack>()->AddWeapon(info->weaponScript);
                }
                else
                {
                    info->weaponScript->Upgrade();
                    info->level++;
                }
                break;
        }
        case(other == m_button3) :
        {
                WeaponInformations* info = m_WeaponChoice[2];
                if(info->level == 1)
                {
                    Player->GetScript<PlayerAttack>()->AddWeapon(info->weaponScript);
                }
                else
                {
                    info->weaponScript->Upgrade();
                    info->level++;
                }
                break;
        }
    }

    m_WeaponChoice.clear();
}


