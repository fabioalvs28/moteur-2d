#pragma once
#include "GameTimer.h"

class Profiler;
class Scene;

class GameManager
{
public:
    ~GameManager();
    GameManager();

    Scene* mpActiveScene;

    int mWindowWidth;
    int mWindowHeight;

    float mAccumulator;

    GameTimer* GetTime();

    void Run();

private:
    Scene* mpNextActiveScene;

    void HandleInput();
    void FixedUpdate();
    void Update();
    void Draw();
    
    Profiler* mProfiler;
    GameTimer mTimer;
    bool IsStopped;

public:
    template<typename T>
    void LaunchScene();

    Scene* GetScene() const { return mpActiveScene; }
    
};

#include "Scene.h"

template <typename T>
void GameManager::LaunchScene()
{
    static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");

    if (mpActiveScene)
    {
        mpNextActiveScene = new T();
        return;
    }

    T* newScene = new T();
    mpActiveScene = newScene;

    //INIT DE LA SCENE
    mpActiveScene->OnEnter();
    Engine::GetECS()->Update();
    mpActiveScene->OnLoad();
}
