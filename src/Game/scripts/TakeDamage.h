#pragma once
#include "scripts/Script.h"

class Health;

class TakeDamage : public IScript
{
public:
	TakeDamage(Health* health) : componentHP(health) {}

	void OnStart() override;
	void OnFixedUpdate() override;
	void ApplyDamage(int damage);
	void OnCollisionEnter(Entity* other) override;
	void OnUpdate() override;

private:
	int damage;
	Health* componentHP;
};