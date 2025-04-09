#include "pch.h"
#include "PlayerAttack.h"

void PlayerAttack::OnUpdate()
{
    for(Weapon* weapon : m_WeaponsList)
    {
        weapon->OnUpdate();
    }
}
