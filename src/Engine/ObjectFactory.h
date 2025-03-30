#pragma once

#include <iostream>

#include "ECS/Components/Camera.h"
#include "ECS/Components/RigidBody2D.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "ECS/Components/Colliders/CircleCollider.h"
#include "scripts/ScriptManager.h"

class ObjectFactory
{
public:
    template <typename T, typename... Args>
    static T* CreateComponent(Entity* entity, Args&&... args);
    template <typename T, typename... Args>
    static T* CreateEntity(Args&&... args);
    template <typename T, typename... Args>
    static T* CreateEntity(Entity* parent, Args&&... args);

    template <typename S, typename ... Args>
    static S* AttachScript(Entity* parent, Args&&... args);

    static void SavePrefab(Entity* entity, const std::string& filename);
    static Entity* LoadPrefab(const std::string& filename);

    
    static std::unordered_map<int, std::function<Component*(Entity*)>> componentRegistry;
};



inline void ObjectFactory::SavePrefab(Entity* entity, const std::string& filename)
{
    json prefabJson;
    prefabJson["Tag"] = entity->GetStringFromTag(entity->GetTag());
    prefabJson["Layer"] =  entity->GetLayer();

    for(auto& component : Engine::GetECS()->GetEntities()[*entity->GetIndex()]->AttachedComponents)
    {
        json componentJson;
        componentJson["bitmask"] = component->GetBitmask();
        component->Serialize(componentJson);
        prefabJson["components"].push_back(componentJson);
    }

    std::ofstream file(filename);
    if (file.is_open())
    {
        file << prefabJson.dump(4);
        file.close();
    }
    else
    {
        std::cout << "Failed to open file " << filename << std::endl;
    }
}

Entity* ObjectFactory::LoadPrefab(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to open file " << filename << std::endl;
        return nullptr;
    }

    json prefabJson;
    file >> prefabJson;
    file.close();

    Entity* entity = CreateEntity<Entity>();

    for(auto& componentInJson : prefabJson["components"])
    {
        int bitmask = componentInJson["bitmask"];
        switch(bitmask)
        {
        case 2:
            RigidBody2D* rb = CreateComponent<RigidBody2D>(entity);
            rb->deserialize(componentInJson);   
            break;
        case 4:
            CreateComponent<SpriteRenderer>(entity);
        case 6:
            CreateComponent<Camera>(entity);
        case 8:
            CreateComponent<Camera>(entity);
        }
        
    }
}

template <typename CType, typename... Args>
CType* ObjectFactory::CreateComponent(Entity* entity, Args&&... args)
{
    return Engine::GetECS()->AddComponent<CType>(entity, args...);
}

template <typename EType, typename ... Args>
EType* ObjectFactory::CreateEntity(Args&&... args)
{
    static_assert(std::is_base_of<Entity, EType>::value, "EType must be a subclass of Entity");
    return Engine::GetECS()->CreateEntity<EType>(args...);
}

template <typename EType, typename ... Args>
EType* ObjectFactory::CreateEntity(Entity* parent, Args&&... args)
{
    static_assert(std::is_base_of<Entity, EType>::value, "EType must be a subclass of Entity");
    EType* entity = Engine::GetECS()->CreateEntity<EType>(parent, args...);
    //parent->GetTransform()->AddChild(dynamic_cast<Entity*>(entity));
    return entity;
}

template <typename S, typename ... Args>
S* ObjectFactory::AttachScript(Entity* owner, Args&&... args)
{
    return Engine::GetScriptManager()->CreateScript<S>(owner, args...);
}

