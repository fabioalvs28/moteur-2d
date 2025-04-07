#include "pch.h"
#include "Weapon.h"

void Weapon::OnStart()
{

}

void Weapon::OnUpdate()
{
	
}

Weapon::Weapon(sf::Vector2f direction)
{
	m_direction = direction;
}

void Weapon::SetWeaponType(WEAPON_TYPES const weaponType)
{
	m_weaponType = weaponType;
}
