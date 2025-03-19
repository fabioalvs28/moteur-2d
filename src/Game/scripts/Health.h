#pragma once

#include "scripts/Script.h"

class Health : public IScript
{
public:
	Health(Entity* entity, int maxHealth) : owner(entity), maxHP(maxHealth), currentHP(maxHealth) {}

	void OnStart() override;
	void OnFixedUpdate() override;
	void SetHP(float HP);

	float GetCurrentHP();
	float GetMaxHP();
	Entity* GetOwner();

	void OnUpdate() override;

private:
	float currentHP;
	float maxHP;
	Entity* owner;
};