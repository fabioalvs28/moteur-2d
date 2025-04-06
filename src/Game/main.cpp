#include "pch.h"
#include "main.h"

#include "Engine.h"
#include "Resources.h"
#include "Managers/GameManager.h"

#include "scenes/GameScene.h"
#include "scenes/TestScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

    srand(time(nullptr));

    Engine::CreateRender();

    Resources::instance().Initialize();
    
    sf::Image icon;
    icon.loadFromFile("../res/PeterIcone.ico");
    Engine::GetRenderWindow()->setIcon(icon);

    Engine::GetGameManager()->LaunchScene<GameScene>();
    
    return 0;
}
