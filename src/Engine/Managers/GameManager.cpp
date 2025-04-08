#include "pch.h"
#include "GameManager.h"

#include "GameTimer.h"
#include "ECS/ECS.h"
#include "ECS/Systems/CollisionSystem.h"
#include "Inputs/Inputs.h"
#include "Inputs/Keyboard.h"
#include "Render/RenderWindow.h"
#include "Utils/Debug.h"
#include "Utils/Profiler.h"

GameManager::~GameManager()
{
}

GameManager::GameManager(): mpActiveScene(nullptr),
                            mWindowWidth(0), mWindowHeight(0),
                            mAccumulator(0), IsStopped(false)
{
    mProfiler = new Profiler();
}

void GameManager::Run()
 
{
 
    Profiler globalProfiler;
 
    while(!IsStopped)
 
    {
 

 
        globalProfiler.NewTask("Global Inputs");
 
        HandleInput();
 
        globalProfiler.EndTask();
 

 
        globalProfiler.NewTask("Update Global");
 
        Update();
 
        globalProfiler.EndTask();
 

 
        globalProfiler.NewTask("Draw Global");
 
        Draw();
 
        globalProfiler.EndTask();
 

 
        if (mpNextActiveScene)
        {
 
            mpActiveScene->OnExit();
 
            delete mpActiveScene;
            
            for (int i = 0; i < Engine::GetECS()->mEntityCount; i++)
            {
                Entity* entity = Engine::GetECS()->GetEntity(i);
 
                Engine::GetScriptManager()->RemoveEntity(entity->GetIndex());
 
                entity->Destroy();
            }

            for (auto& all_cell : Engine::GetCollisionSystem()->mGrid->GetAllCells())
            {
                all_cell.second.clear();
            }
            
            Engine::GetCollisionSystem()->mPreviousCollisions.clear();
            
            mpActiveScene = mpNextActiveScene;
 
            mpNextActiveScene = nullptr;
            
            mpActiveScene->OnEnter();
            
            Engine::GetECS()->Update();
            
            Update();
        }
 
    }
    
    delete mpActiveScene;
 
}

void GameManager::HandleInput()
{
    if (Engine::GetRenderWindow()->hasFocus()) {
        while (const std::optional<sf::Event> event = Engine::GetRenderWindow()->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                IsStopped = true;
                Engine::GetRenderWindow()->close();
            }
        }

        if (Keyboard::GetKeyDown(Keyboard::Key::Escape))
        {
            IsStopped = true;
            Engine::GetRenderWindow()->close();
        }

        Inputs::UpdateKeyboard();
        Inputs::UpdateMouse();
    }
}


void GameManager::FixedUpdate()
{
    mpActiveScene->OnFixedUpdate();
    
    Engine::GetECS()->FixedUpdate();
    
}

void GameManager::Draw()
{

    Engine::GetRenderWindow()->BeginFrame();
    
    mProfiler->NewTask("Draw window");
    Engine::GetECS()->Draw();
    mProfiler->EndTask();

    Engine::GetRenderWindow()->EndFrame();
    
}

GameTimer* GameManager::GetTime()
{
    return &mTimer;
}

void GameManager::Update()
{
    const int MAX_PHYSICS_STEPS = 1;
    int steps = 0;
    
    mTimer.UpdateTime();
    // Debug::Log("FPS " + std::to_string(mTimer.GetFPS()));
    // Debug::Log("Entity count " + std::to_string(Engine::GetECS()->mEntityCount));

    mAccumulator += mTimer.GetDeltaTime();
    mProfiler->NewTask("Physics update");
    while(mAccumulator >= FIXED_DT && steps < MAX_PHYSICS_STEPS)
    {
        FixedUpdate();
        mAccumulator -= FIXED_DT;
        steps++;
    }
    if (steps == MAX_PHYSICS_STEPS)
    {
        mAccumulator = 0.0;
    }
    mProfiler->EndTask();

    mProfiler->NewTask("Update ECS");
    Engine::GetECS()->Update();
    mProfiler->EndTask();
    
    mProfiler->NewTask("Update scene");
    mpActiveScene->OnUpdate();
    mProfiler->EndTask();
    
}


