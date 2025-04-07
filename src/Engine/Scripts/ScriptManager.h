#pragma once
#include <map>

#include "Render/RenderWindow.h"

class ObjectFactory;
class Entity;
struct IScript;

class ScriptManager
{
public:
    ScriptManager();
    
    template <typename SType, typename ... Args>    
    SType* CreateScript(Entity* entity, Args&&... args);
    
    void RemoveEntity(int* index);

    void OnCollisionEnter(Entity* collider, Entity* other);
    void OnTriggerEnter(Entity* collider, Entity* other);

    void OnCollisionStay(Entity* collider, Entity* other);
    void OnTriggerStay(Entity* collider, Entity* other);

    void OnCollisionExit(Entity* collider, Entity* other);
    void OnTriggerExit(Entity* collider, Entity* other);
    
    void OnRender(RenderWindow* window);
    
    void OnFixedUpdate();
    void OnUpdate();
    static IScript* CreateScriptByName(const std::string& scriptName);
    
    static void RegisterScript(const std::string& name, IScript* script);
private:
    std::unordered_map<std::string, IScript*> mScriptRegistry;
    std::map<int*, std::vector<IScript*>> scriptedEntity;
    std::map<int*, std::vector<IScript*>> scriptedEntityToAdd;
    int mEntityToRemoveCount;
    int** toRemoveId = new int*[1024];


    friend class Entity;
    friend ObjectFactory;
};

#include "ScriptManager.inl"