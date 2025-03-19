#include "pch.h"
#include "TakeDamage.h"

void TakeDamage::OnStart()
{
}

void TakeDamage::OnFixedUpdate()
{
}

void TakeDamage::OnCollisionEnter(Entity* other)
{
	if (other->IsTag(Entity::Tag::PLAYER)) {

	}
}

void TakeDamage::OnUpdate()
{
}
