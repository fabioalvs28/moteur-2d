#include "pch.h"
#include "Bomb.h"

#include "ObjectFactory.h"
#include "WeaponAttack.h"
#include "scripts/PlayerAttack.h"

void Bomb::OnStart()
{
    m_attackDistance = 0.0f;
    m_attackDelay = 10.0f;
    m_pGameManager = Engine::GetGameManager();
    m_velocity = 0.0f;
    m_damages = 5.0f;
    m_lifeSpan = 2.0f;
    m_time = 0.0f;
    m_weaponType = TYPE_BOMB;
    m_level = 1;
    m_direction = { 1.0f,1.0f};
    Engine::GetEntityByName("player")->GetScript<PlayerAttack>()->AddWeapon(this);
    mp_CamPos = Engine::GetEntityByName("camera")->GetTransform();
}

void Bomb::OnUpdate()
{
    m_time += Engine::GetDeltaTime();
    if(m_time >= m_attackDelay)
    {
        OnAttack();
        m_time = 0.0f;
    }
}

void Bomb::OnAttack()
{
    srand(time(NULL));
    Entity* attackCircle = ObjectFactory::CreateEntity<Entity>();
    sf::Vector2f randPos = sf::Vector2f(rand() % Engine::GetRenderWindow()->getSize().x, rand() % Engine::GetRenderWindow()->getSize().y);
    attackCircle->GetTransform()->position = mp_CamPos->position + randPos;
    SpriteRenderer* sr = ObjectFactory::CreateComponent<SpriteRenderer>(attackCircle, Resources::instance().DEFAULT_SPRITE);
    CircleCollider* coll =  ObjectFactory::CreateComponent<CircleCollider>(attackCircle, 5000.0f);
    coll->SetTrigger(true);
    ObjectFactory::AttachScript<WeaponAttack>(attackCircle, m_damages, m_attackDistance, m_velocity, m_lifeSpan, m_direction);
}