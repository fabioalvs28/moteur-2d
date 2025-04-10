#include "pch.h"
#include "WeaponContainer.h"

#include "ObjectFactory.h"
#include "ECS/Components/ui/Image.h"

void WeaponContainer::OnStart()
{
    Entity* sword = ObjectFactory::CreateEntity<Entity>(1);
    ObjectFactory::CreateComponent<Image>(sword, Resources::instance().SWORD, sf::Vector2f(0.0f,0.0f), sf::Vector2f(0.75f,0.75f));
    m_WeaponsIconsList.push_back(sword);
}

void WeaponContainer::AddWeapons(Sprite* nWeaponsIcon)
{
    for (Entity* entity : m_WeaponsIconsList)
    {
        Image* image = entity->GetComponent<Image>();
        if (image && image->UIImage == nWeaponsIcon)
        {
            return; 
        }
    }

    Entity* nWeapons = ObjectFactory::CreateEntity<Entity>(1);
    ObjectFactory::CreateComponent<Image>(nWeapons, nWeaponsIcon,sf::Vector2f(0.0f, m_WeaponsIconsList.size() * 64.0f),sf::Vector2f(0.75f, 0.75f));

    m_WeaponsIconsList.push_back(nWeapons);
}

void WeaponContainer::AddBuffs(Sprite* nBuffsIcon)
{
    for (Entity* entity : m_BuffsIconsList)
    {
        Image* image = entity->GetComponent<Image>();
        if (image && image->UIImage == nBuffsIcon)
        {
            return; 
        }
    }

    Entity* nBuffs = ObjectFactory::CreateEntity<Entity>(1);
    ObjectFactory::CreateComponent<Image>(nBuffs, nBuffsIcon,sf::Vector2f(64.0f, m_BuffsIconsList.size() * 64.0f),sf::Vector2f(0.75f, 0.75f));

    m_BuffsIconsList.push_back(nBuffs);
}
