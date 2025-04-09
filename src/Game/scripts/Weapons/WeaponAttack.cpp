#include "pch.h"
#include "WeaponAttack.h"

#include "Transform.h"
#include "scripts/EnnemyAttack.h"

WeaponAttack::WeaponAttack(float damage, float attackDistance, float velocity, float lifespan ,sf::Vector2f direction) : m_damage(damage), m_attackDistance(attackDistance), m_velocity(velocity), m_direction(direction), m_lifeSpan(lifespan)
{
}

void WeaponAttack::OnStart()
{
    mp_OwnerTransform = m_pOwner->GetTransform();
    //mp_OwnerTransform->SetPosition(mp_OwnerTransform->position.x + m_direction.x * m_attackDistance * m_velocity , mp_OwnerTransform->position.y + m_direction.y * m_attackDistance * m_velocity);
}

void WeaponAttack::OnUpdate()
{
    m_time += Engine::GetDeltaTime();
    if (m_time >= m_lifeSpan)
    {
        m_pOwner->Destroy();
    }
}

void WeaponAttack::OnFixedUpdate()
{
    // if(m_velocity != 0.0f)
    //     mp_OwnerTransform->SetPosition(mp_OwnerTransform->position.x + m_direction.x * m_attackDistance * m_velocity , mp_OwnerTransform->position.y + m_direction.y * m_attackDistance * m_velocity);

}

void WeaponAttack::OnTriggerStay(Entity* other)
{
    if(other->IsTag(Entity::Tag::ENEMY))
    {
        other->GetScript<EnemyAttack>()->TakeDamage(m_damage);
    }
}

