#pragma once

#include <iostream>

#include "ECS/Components/Camera.h"
#include "ECS/Components/PhysicsMaterial.h"
#include "ECS/Components/RigidBody2D.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "ECS/Components/Colliders/CircleCollider.h"
#include "Game/Resources.h"
#include "Transform.h"
#include "Scripts/Script.h"
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

    static void AddScript(IScript* script, Entity* entity);
    static std::unordered_map<int, std::function<Component*(Entity*)>> componentRegistry;
};

inline void ObjectFactory::AddScript(IScript* script, Entity* entity)
{
    script->SetOwner(entity);
    Engine::GetScriptManager()->scriptedEntityToAdd[entity->GetIndex()].push_back(script);
}

inline void ObjectFactory::SavePrefab(Entity* entity, const std::string& filename)
{
    json prefabJson;
    prefabJson["Name"] = entity->GetName();
    prefabJson["TPosition"] = {{"x", entity->GetTransform()->position.x}, {"y", entity->GetTransform()->position.y}};
    prefabJson["TScale"] = {{"x", entity->GetTransform()->scale.x}, {"y", entity->GetTransform()->scale.y}};
    prefabJson["Rotation"] = entity->GetTransform()->rotation.asDegrees();
    prefabJson["Tag"] = entity->GetStringFromTag(entity->GetTag());
    prefabJson["Layer"] =  entity->GetLayer();

    for(auto& script : Engine::GetScriptManager()->scriptedEntity[entity->GetIndex()])
    {
        json scriptJson;
        scriptJson["Name"] = CoreUtils::type(*script);
        prefabJson["Scripts"].push_back(scriptJson);
    }
    
    for(auto& component : Engine::GetECS()->GetEntities()[*entity->GetIndex()]->AttachedComponents)
    {
        json componentJson;
        component->Serialize(componentJson);
        componentJson["bitmask"] = component->GetBitmask();
        prefabJson["components"].push_back(componentJson);
    }
    
    if(std::filesystem::exists(filename))
    {
        std::cout << "Already exists " << filename << std::endl;
        return;
    }
    
    std::ofstream outfile(filename);


    if (outfile.is_open())
    {
        outfile << prefabJson.dump(4);
        outfile.close();
    }
    else
    {
        std::cout << "Failed to open file " << filename << std::endl;
    }
}

inline Entity* ObjectFactory::LoadPrefab(const std::string& filename)
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

    Entity* entity = CreateEntity<Entity>(prefabJson["Layer"]);
    entity->SetName( prefabJson["Name"]);
    entity->GetTransform()->position.x = prefabJson["TPosition"]["x"];
    entity->GetTransform()->position.y = prefabJson["TPosition"]["y"];
    entity->GetTransform()->scale.x = prefabJson["TScale"]["x"];
    entity->GetTransform()->scale.y = prefabJson["TScale"]["y"];
    entity->GetTransform()->rotation = sf::degrees(prefabJson["Rotation"]);
    entity->SetTag(entity->GetTagFromString(prefabJson["Tag"]));
    
    for(auto& componentInJson : prefabJson["components"])
    {
        int bitmask = componentInJson["bitmask"];
        switch(bitmask)
        {
            case 2: // 1 << 1
                {
                    RigidBody2D* rb = CreateComponent<RigidBody2D>(entity);
                    rb->Deserialize(componentInJson);    
                }
                break;
            case 4: // 1 << 2
                {
                    SpriteRenderer* sprite = CreateComponent<SpriteRenderer>(entity, Resources::instance().DEFAULT_SPRITE);
                    sprite->Deserialize(componentInJson);
                }
                break;
            case 8: // 1 << 3
                {
                    Camera* cam = CreateComponent<Camera>(entity);
                    cam->Deserialize(componentInJson);
                }
                break;
            case 16: // 1 << 4
                {
                    PhysicsMaterial* mat = CreateComponent<PhysicsMaterial>(entity);
                    mat->Deserialize(componentInJson);
                }
                break;
            case 32: // 1 << 5
                break;
            case 64: // 1 << 6
                break;
            case 128: // 1 << 7
                break;
            case 256: // 1 << 8
                break;
            case 512: // 1 << 9
                {
                    CircleCollider* coll = CreateComponent<CircleCollider>(entity);
                    coll->Deserialize(componentInJson);
                }
                break;            
            case 1024: // 1 << 10
                {
                    AABBCollider* coll = CreateComponent<AABBCollider>(entity);
                    coll->Deserialize(componentInJson);
                }
                break;
        default:
            break;
        }
    }

    for(auto& scriptInJson : prefabJson["Scripts"])
    {
        std::string name = scriptInJson["Name"];
        
        IScript* script = ScriptManager::GetScriptByName(name);

        AddScript(script, entity);
    }
    return entity;
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

