
#include "pch.h"
#include "Sword.h"

#include "ObjectFactory.h"
#include "Managers/GameManager.h"
#include "Transform.h"
#include "WeaponAttack.h"
#include "../EnnemyAttack.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "scripts/PlayerAttack.h"


void Sword::OnStart()
{
    mp_PlayerMovement = Engine::GetEntityByName("player")->GetScript<PlayerMovement>();
    m_attackDistance = 100.0f;
    m_attackDelay = 2.0f;
    m_time = 0.0f;
    m_pGameManager = Engine::GetGameManager();
    m_velocity = 0.0f;
    m_lifeSpan = 2.0f;
    m_damages = 5.0f;
    m_weaponType = TYPE_SWORD;
    m_level = 1;
    Engine::GetEntityByName("player")->GetScript<PlayerAttack>()->AddWeapon(this);
}

void Sword::OnUpdate()
{
    m_direction = mp_PlayerMovement->GetDirection();
    m_time += Engine::GetDeltaTime();
    if(m_time >= m_attackDelay)
    {
        OnAttack();
        m_time = 0.0f;
    }
}

void Sword::OnAttack()
{
    switch (m_level)
    {
    case 1:
    {
        SpriteRenderer* playerSprite = Engine::GetEntityByName("player")->GetComponent<SpriteRenderer>();
        sf::Vector2f playerTextRect = sf::Vector2f(playerSprite->Image->getTextureRect().size.x / 2, playerSprite->Image->getTextureRect().size.y / 2);
        Entity* attackRect = ObjectFactory::CreateEntity<Entity>();
        //SpriteRenderer* sr = ObjectFactory::CreateComponent<SpriteRenderer>(attackRect, Resources::instance().DEFAULT_SPRITE);
        Animator* pAnim = ObjectFactory::CreateComponent<Animator>(attackRect, Resources::instance().VFX_SLASH, 0.1f);
        sf::Vector2f textRect = sf::Vector2f(pAnim->mp_SpriteSheet->getTextureRect().size.x / 2, pAnim->mp_SpriteSheet->getTextureRect().size.y / 2);
        float rotation = atan2(m_direction.y, m_direction.x);
        attackRect->GetTransform()->rotation = sf::radians(rotation);
        attackRect->GetTransform()->position = m_pOwner->GetTransform()->position + m_direction * m_attackDistance;;

        AABBCollider* coll = ObjectFactory::CreateComponent<AABBCollider>(attackRect, 0, 0, 100, 100);
        ObjectFactory::AttachScript<WeaponAttack>(attackRect, m_damages, m_attackDistance, 0.0, m_direction);
        coll->SetTrigger(true);

        break;
    }
    default:
        break;
    }
    
}

void Sword::Upgrade()
{
    m_level++;
    m_damages *= 1.10f;
}
