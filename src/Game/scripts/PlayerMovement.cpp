#include "pch.h"
#include "PlayerMovement.h"

#include "Experience.h"
#include "Managers/GameManager.h"

#include "ObjectFactory.h"
#include "Resources.h"
#include "Transform.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/ui/ProgressBar.h"
#include "ECS/Components/Animator.h"
#include "ECS/Components/ui/Button.h"
#include "scenes/TestScene.h"
#include "scripts/Weapons/Sword.h"

void PlayerMovement::OnStart()
{
    m_experience = 0;
    m_maxExp = 100;
    m_direction = sf::Vector2f(1.0, 0.0);
    m_speed = 200.0f;
    m_hp = 1.0f;
    m_maxHp = 100.0f;
    m_rw = Engine::GetRenderWindow();
    m_pTransform = m_pOwner->GetTransform();
    m_pGameManager = Engine::GetGameManager();
    mp_MusicScript = m_pOwner->GetScript<MusicScript>();
    m_pCamera = Engine::GetEntityByName("camera");

    sf::Vector2f scaleExp = sf::Vector2f(8.0f, 3.0f);
    Entity* UI_ExpBar = ObjectFactory::CreateEntity<Entity>();
    m_pExpBar = ObjectFactory::CreateComponent<ProgressBar>(UI_ExpBar, Resources::instance().BAR_CONTAINER, Resources::instance().BAR_EXP,
        sf::Vector2f(m_rw->GetWindowWidth() / 2 - Resources::instance().BAR_CONTAINER->getTexture().getSize().x * scaleExp.x / 2, 20.0f), sf::Vector2f(4.5f * scaleExp.x, 4.0f * scaleExp.y));
    
    m_pExpBar->Scale = sf::Vector2f(scaleExp.x, scaleExp.y);

    sf::Vector2f scaleHP = sf::Vector2f(4.5f, 2.0f);
    Entity* UI_HealthBar = ObjectFactory::CreateEntity<Entity>();
    m_pHealthBar = ObjectFactory::CreateComponent<ProgressBar>(UI_HealthBar, Resources::instance().BAR_CONTAINER, Resources::instance().BAR_HEALTH,
        sf::Vector2f(m_rw->GetWindowWidth() / 2 - Resources::instance().BAR_CONTAINER->getTexture().getSize().x * scaleHP.x / 2, 60.0f), sf::Vector2f(4.5f * scaleHP.x, 4.0f * scaleHP.y));

    m_pHealthBar->Scale = sf::Vector2f(scaleHP.x, scaleHP.y);

    m_pExpBar->Maximum = m_maxExp;
    m_pHealthBar->Progress = m_hp;
    m_pHealthBar->Maximum = m_maxHp;

}

void PlayerMovement::OnFixedUpdate()
{
    m_pTransform->SetPosition(m_pTransform->position.x + m_movement.x * m_speed, m_pTransform->position.y + m_movement.y * m_speed);
    m_movement = sf::Vector2f(0, 0);
    m_pCamera->GetTransform()->position = m_pTransform->position - sf::Vector2f(m_rw->GetWindowWidth() *0.5f, m_rw->GetWindowHeight() *0.5f);
}

void PlayerMovement::OnCollisionEnter(Entity* other)
{
    if (other->IsTag(Entity::Tag::XP))
    {
        m_experience += other->GetScript<Experience>()->GetValue();
        if (m_experience >= m_maxExp)
        {
            LevelUp();
        }
        other->Destroy();
    }
}

void PlayerMovement::OnUpdate()
{
    m_pHealthBar->Progress = m_hp;
    m_pHealthBar->Maximum = m_maxHp;

    m_pExpBar->Progress = m_experience;

    if (m_experience >= m_maxExp)
    {
        LevelUp();
    }

    if (isKeyPressed(sf::Keyboard::Key::D))
    {
        m_movement += m_pOwner->GetTransform()->right * Engine::GetDeltaTime();
        m_direction = sf::Vector2f(1.0, 0.0);
    }
    if (isKeyPressed(sf::Keyboard::Key::Q))
    {
        m_movement -= m_pOwner->GetTransform()->right * Engine::GetDeltaTime();
        m_direction = sf::Vector2f(-1.0, 0.0);
    }
    if (isKeyPressed(sf::Keyboard::Key::S))
    {
        m_movement += m_pOwner->GetTransform()->up * Engine::GetDeltaTime();
        m_direction = sf::Vector2f(0.0, 1.0);
    }
    if (isKeyPressed(sf::Keyboard::Key::Z))
    {
        m_movement -= m_pOwner->GetTransform()->up * Engine::GetDeltaTime();
        m_direction = sf::Vector2f(0.0, -1.0);
    }

    //m_pCamera->GetTransform()->SetPosition(m_pOwner->GetTransform()->position.x - Engine::GetRenderWindow()->GetWindowWidth() * 0.5f, m_pOwner->GetTransform()->position.y - Engine::GetRenderWindow()->GetWindowHeight() * 0.5f);

}


void PlayerMovement::OnDisable()
{
    
}


void PlayerMovement::LevelUp()
{
    m_experience -= m_maxExp;
    m_maxExp += 5;
    m_pExpBar->Maximum = m_maxExp;
    
    Engine::GetGameManager()->GetTime()->Pause();

    if(!mp_LevelUpMenu)
        mp_LevelUpMenu = m_pOwner->GetScript<LevelUpMenu>();

    mp_LevelUpMenu->OnSpawn();
    
}

void PlayerMovement::TakeDamage(float damage)
{
    srand(time(NULL));

    int random = rand() % 2;
    switch (random)
    {
        case 0:
            mp_MusicScript->PlaySoundScript("HurtSound1");
            break;
        case 1:
            mp_MusicScript->PlaySoundScript("HurtSound2");
            break;
    }
    m_hp -= damage;
    if (m_hp <= 0)
        Die();
}

void PlayerMovement::Die()
{
    m_hp = 0;
    Engine::GetGameManager()->GetTime()->Pause();
    Entity* text = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Text>(text, Resources::instance().DEFAULT_FONT, 125, "Peter est MORT",sf::Vector2f(Engine::GetRenderWindow()->GetWindowWidth()* 0.5f - 350.0f, Engine::GetRenderWindow()->GetWindowHeight() * 0.5f - 150.0f));

    ObjectFactory::CreateComponent<Button>(text, Resources::instance().KONG_BUTTON, sf::Vector2f(Engine::GetRenderWindow()->GetWindowWidth() * 0.5f - 150.0f, Engine::GetRenderWindow()->GetWindowHeight() * 0.5f + 150.0f), Resources::instance().BUTTON_KONG_TEXTURE->getSize().x, Resources::instance().BUTTON_KONG_TEXTURE->getSize().y,
        [this]()
        {
            Engine::GetGameManager()->GetTime()->Resume();
            Engine::GetGameManager()->LaunchScene<TestScene>();
        },[this](){});
}
