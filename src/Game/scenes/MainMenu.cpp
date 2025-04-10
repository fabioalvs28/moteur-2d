#include "pch.h"
#include "MainMenu.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "Managers/GameManager.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/ui/Image.h"
#include "ECS/Components/ui/Button.h"
#include "ECS/Components/ui/ProgressBar.h"
#include "ECS/Components/ui/Text.h"

#include "../Game/scenes/TestScene.h"

void MainScene::OnEnter()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Resources::instance().Initialize();

    RenderWindow* pWin = Engine::GetRenderWindow();
    Entity* pCam = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Camera>(pCam);
    pCam->SetName("camera");

    
    Entity* mainMenu = ObjectFactory::CreateEntity<Entity>(5);
    sf::Sprite sprite = Resources::instance().UI_SHEET->CreateSpriteAt(sf::Vector2i(32, 1120), sf::Vector2i(182, 279));
    ObjectFactory::CreateComponent<Image>(mainMenu, new Sprite(sprite),
        sf::Vector2f(pWin->getSize().x / 2 - 325 / 2, 50.0f), sf::Vector2f(2.5, 2.5));
    
    Entity* decorations = ObjectFactory::CreateEntity<Entity>(6);
    sf::Sprite decoration = Resources::instance().UI_SHEET->CreateSpriteAt(sf::Vector2i(267, 1134), sf::Vector2i(182, 279));
    ObjectFactory::CreateComponent<Image>(decorations, new Sprite(decoration), sf::Vector2f(pWin->getSize().x / 2 - 279 / 2, 85.0f), sf::Vector2f(2.5, 2.5));

    Entity* buttonPlay = ObjectFactory::CreateEntity<Entity>(6);
    sf::Sprite pb = Resources::instance().UI_SHEET->CreateSpriteAt(sf::Vector2i(51, 1556), sf::Vector2i(109 - 51, 1579 - 1556));
    ObjectFactory::CreateComponent<Button>(buttonPlay, new Sprite(pb), sf::Vector2f(pWin->getSize().x / 2 - (1579 - 1556) * 4 / 2, 300.0f), sf::Vector2f(4.0f, 3.0f), (109 - 51) * 4, (1579 - 1556) * 3,
        [this] 
        {
            Engine::GetGameManager()->LaunchScene<TestScene>();
        }, [this]{});
    ObjectFactory::CreateComponent<Text>(buttonPlay, Resources::instance().DEFAULT_FONT, 32, "PLAY", 
        sf::Vector2f(pWin->getSize().x / 2 - (1579 - 1556) * 4 / 2 + 85, 315.0f));
}

void MainScene::OnLoad()
{

}



