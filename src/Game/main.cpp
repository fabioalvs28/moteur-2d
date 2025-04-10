#include "pch.h"
#include "main.h"

#include "Engine.h"
#include "Resources.h"
#include "Managers/GameManager.h"

#include "scenes/TestScene.h"
#include "scenes/MainMenu.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

    srand(time(nullptr));

    Engine::CreateRender();

    Resources::instance().Initialize();

    Engine::GetGameManager()->LaunchScene<MainScene>();
    Engine::GetGameManager()->Run();
    
    return 0;
}
