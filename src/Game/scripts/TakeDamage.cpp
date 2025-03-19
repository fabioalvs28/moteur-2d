#include "pch.h"

#include "TakeDamage.h"
#include "Health.h"

void TakeDamage::OnStart()
{
}

void TakeDamage::OnFixedUpdate()
{
}

void TakeDamage::ApplyDamage(int damage)
{
	if (componentHP)
	{
		int newHP = componentHP->GetCurrentHP() - damage;
		componentHP->SetHP(newHP);
	}

	if (componentHP <= 0)
	{
		Entity* owner = componentHP->GetOwner();
		if (owner)
		{
			owner->Destroy();
		}
	}
}

void TakeDamage::OnCollisionEnter(Entity* other)
{
	if (other->IsTag(Entity::Tag::PLAYER)) {
		int damageAmount = 10;
		this->ApplyDamage(damageAmount);
	}
}

void TakeDamage::OnUpdate()
{
}
