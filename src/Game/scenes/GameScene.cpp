#include "pch.h"
#include "GameScene.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/ui/ProgressBar.h"
#include "scripts/EnnemyAttack.h"
#include "scripts/WaveManager.h"

#include "scripts/PlayerMovement.h"


void GameScene::OnEnter()
{
    RenderWindow* pWindow = Engine::GetRenderWindow();
    srand(static_cast<unsigned int>(time(nullptr)));

    Entity* player = ObjectFactory::CreateEntity<Entity>();
    SpriteRenderer* sr = ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().DEFAULT_SPRITE);
    ObjectFactory::CreateComponent<AABBCollider>(player);
    sf::Vector2f playerSize = (sf::Vector2f)sr->Image->getTexture().getSize();
    //sr->Image->setOrigin({ playerSize.x * 0.5f, playerSize.y *  0.5f });
    player->GetTransform()->SetPosition(pWindow->GetWindowWidth() / 2 + playerSize.x, pWindow->GetWindowHeight() / 2 + playerSize.y);
    player->SetTag(Entity::Tag::PLAYER);


    Entity* camera = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Camera>(camera);
    camera->SetName("camera");

    PlayerMovement* ppm = ObjectFactory::AttachScript<PlayerMovement>(player);
    ppm->Attack();


}

void GameScene::OnLoad()
{
    //Entity* enemy = ObjectFactory::CreateEntity<Entity>();
    //ObjectFactory::AttachScript<WaveManager>(enemy);
}

void GameScene::OnUpdate()
{

}