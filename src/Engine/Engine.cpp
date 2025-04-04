#include "pch.h"
#include "Engine.h"


#include "ObjectFactory.h"
#include "ECS/Systems/CameraSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/ParticleSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "Managers/GameManager.h"
#include "scripts/ScriptManager.h"

#include "ECS/ECS.h"
#include "Render/RenderWindow.h"

#include "Engine/Scripts/ScriptRegistry.h"
#include <regex>
#include <filesystem>

IScript* CreateScriptInstance(const std::string& scriptName)
{
    auto& registry = GetScriptRegistry();
    auto it = registry.find(scriptName);
    if (it != registry.end())
    {
        return it->second();
    }
    return nullptr;
}

void SearchAndRegisterScripts(const std::string& folderPath)
{
    namespace fs = std::filesystem;

    std::regex registerScriptRegex(R"(REGISTER_SCRIPT\(\s*(\w+)\s*\))");

    for (const auto& entry : fs::recursive_directory_iterator(folderPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".cpp")
        {
            std::ifstream file(entry.path());
            if (file.is_open())
            {
                std::string line;
                while (std::getline(file, line))
                {
                    std::smatch match;
                    if (std::regex_search(line, match, registerScriptRegex))
                    {
                        std::string scriptName = match[1].str();

                        IScript* scriptInstance = CreateScriptInstance(scriptName);
                        if (scriptInstance)
                        {
                            Engine::GetScriptManager()->RegisterScript(scriptName, scriptInstance);
                        }
                    }
                }
                file.close();
            }
        }
    }
}


Engine::Engine() : mGameManager(new GameManager()), mECS(new ECS()), mRenderSystem(nullptr),
                   mPhysicsSystem(new PhysicsSystem()), mCollisionSystem(new CollisionSystem()), mCameraSystem(nullptr),
                   mParticleSystem(nullptr),
                   mScriptManager(new ScriptManager()),
                   mRenderWindow(nullptr)
{
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    SearchAndRegisterScripts("..\\..\\src\\Game");
}

Engine::~Engine()
{
    delete mGameManager;

    delete mECS;
    delete mRenderSystem;
    delete mPhysicsSystem;
    delete mCollisionSystem;
    delete mCameraSystem;
    delete mParticleSystem;
    delete mScriptManager;

    delete mRenderWindow;
}

Entity* Engine::GetEntityByName(std::string name)
{
    return GetECS()->GetEntityByName(name);
}

void Engine::CreateRender()
{
    RenderWindow* window = instance().mRenderWindow;
    if (window) return;
    
    window = new RenderWindow("La window", 1600, 900);
    
    instance().mCameraSystem = new CameraSystem(window);
    instance().mRenderSystem = new RenderSystem(window);
    instance().mParticleSystem = new ParticleSystem(window);

    instance().mRenderWindow = window;
}

GameManager* Engine::GetGameManager()
{
    return instance().mGameManager;
}

CameraSystem* Engine::GetCameraSystem()
{
    return instance().mCameraSystem;
}

RenderWindow* Engine::GetRenderWindow()
{
    return instance().mRenderWindow;
}

RenderSystem* Engine::GetRenderSystem()
{
    return instance().mRenderSystem;
}

PhysicsSystem* Engine::GetPhysicsSystem()
{
    return instance().mPhysicsSystem;
}

CollisionSystem* Engine::GetCollisionSystem()
{
    return instance().mCollisionSystem;
}

ParticleSystem* Engine::GetParticleSystem()
{
    return instance().mParticleSystem;
}

ScriptManager* Engine::GetScriptManager()
{
    return instance().mScriptManager;
}

float Engine::GetDeltaTime()
{
    return instance().mGameManager->GetTime()->GetDeltaTime();
}

ECS* Engine::GetECS()
{
    return instance().mECS;
}
