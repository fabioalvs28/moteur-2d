#pragma once
#include "scripts/Script.h"

class Health : public IScript
{
public:

	void OnStart() override;
	void OnFixedUpdate() override;
	void SetHP(float HP);
	float GetCurrentHP();
	float GetMaxHP();
	void OnUpdate() override;

private:
	float currentHP;
	float maxHP;
};

