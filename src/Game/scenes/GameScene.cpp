#include "pch.h"
#include "GameScene.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"
#include "ECS/Components/ui/Image.h"

#include "scripts/PlayerMovement.h"

void GameScene::OnEnter()
{
    m_pRenderWindow = Engine::GetRenderWindow();
    srand(static_cast<unsigned int>(time(nullptr)));
    
    m_pPlayer = ObjectFactory::CreateEntity<Entity>();
    RenderWindow* pWindow = Engine::GetRenderWindow();
    m_pPlayer->GetTransform()->SetPosition(pWindow->GetWindowWidth() / 2, pWindow->GetWindowHeight() / 2);
    ObjectFactory::CreateComponent<SpriteRenderer>(m_pPlayer, Resources::instance().DEFAULT_SPRITE);
    m_pPlayer->SetTag(Entity::Tag::PLAYER);
    
    ObjectFactory::AttachScript<PlayerMovement>(m_pPlayer);
    
    m_pCamera = ObjectFactory::CreateEntity<Entity>(m_pPlayer);
    ObjectFactory::CreateComponent<Camera>(m_pCamera);

    //Entity* expBar = ObjectFactory::CreateEntity<Entity>();
    //ObjectFactory::CreateComponent<Image>(expBar, Resources::instance().DEFAULT_SPRITE);
    
}

void GameScene::OnUpdate()
{
    float windowWidth = m_pRenderWindow->GetWindowWidth();
    float windowheight = m_pRenderWindow->GetWindowHeight();
    m_pCamera->GetTransform()->position = m_pPlayer->GetTransform()->position - sf::Vector2f(windowWidth / 2, windowheight / 2);
}