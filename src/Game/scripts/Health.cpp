#include "pch.h"
#include "Health.h"

void Health::OnStart()
{
}

void Health::OnFixedUpdate()
{
}

void Health::SetHP(float HP)
{
	currentHP = HP;
}

float Health::GetCurrentHP()
{
	return currentHP;
}

float Health::GetMaxHP()
{
	return maxHP;
}

void Health::OnUpdate()
{
}
