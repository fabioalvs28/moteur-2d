#pragma once
#include <windows.h>


class RenderWindow;
class ScriptManager;
class ParticleSystem;
class CollisionSystem;
class PhysicsSystem;
class CameraSystem;
class RenderSystem;
class ECS;
class GameManager;
class ObjectFactory;
struct IScript;
class Entity;

class Engine
{
public:
    Engine();
    ~Engine();
    
    static Entity* GetEntityByName(std::string name);

    static void CreateRender();
    static RenderWindow* GetRenderWindow();
    
    static GameManager* GetGameManager();

    static CameraSystem* GetCameraSystem();

    static ScriptManager* GetScriptManager();

    static float GetDeltaTime();

private:
    static Engine& instance()
    {
        static Engine game;
        return game;
    }

    static ECS* GetECS();
    static RenderSystem* GetRenderSystem();
    static PhysicsSystem* GetPhysicsSystem();
    static CollisionSystem* GetCollisionSystem();
    static ParticleSystem* GetParticleSystem();

    GameManager* mGameManager;

    ECS* mECS;
    RenderSystem* mRenderSystem;
    PhysicsSystem* mPhysicsSystem;
    CollisionSystem* mCollisionSystem;
    CameraSystem* mCameraSystem;
    ParticleSystem* mParticleSystem;
    ScriptManager* mScriptManager;
    RenderWindow* mRenderWindow;

    // Make system only accessible from engine
    friend class Entity;
    friend class ECS;
    
    friend class ObjectFactory;
    friend struct IScript;
    friend class GameManager;
    friend class RenderSystem;
    friend class PhysicsSystem;
    friend class CollisionSystem;
    friend class CameraSystem;
    friend class ScriptManager;
};


