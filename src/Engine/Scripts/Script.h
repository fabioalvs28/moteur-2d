#pragma once
#include "ECS/Entity.h"
#include "ScriptManager.h"

struct IScript
{
#define REGISTER_SCRIPT(scriptInstance) \
    Engine::GetScriptManager()->RegisterScript((scriptInstance).GetName(), &(scriptInstance))
    
    IScript();
    virtual ~IScript() = default;
    
    virtual void OnStart();
    virtual void OnUpdate();
    virtual void OnFixedUpdate();

    virtual void OnCollisionEnter(Entity* other);
    virtual void OnCollisionStay(Entity* other);
    virtual void OnCollisionExit(Entity* other);

    virtual void OnTriggerEnter(Entity* other);
    virtual void OnTriggerStay(Entity* other);
    virtual void OnTriggerExit(Entity* other);

    virtual void OnRender(RenderWindow* window);
    std::string& GetName() { return mName; }
    virtual void OnRenderDisable();
    virtual void OnDisable();

protected:
    Entity* owner;
    std::string mName;

private:
    void SetOwner(Entity* entity);
    friend ScriptManager;
    friend ObjectFactory;
};

