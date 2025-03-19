#pragma once
#include "scripts/Script.h"

class Health;

class TakeDamage : public IScript
{
public:
	TakeDamage() = default;

	void OnStart() override;
	void OnFixedUpdate() override;
	void OnCollisionEnter(Entity* other) override;
	void OnUpdate() override;

private:
	float damage;
};