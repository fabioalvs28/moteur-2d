#pragma once

#include <map>
#include <vector>
class Component;
class Entity;

struct EC
{
    Entity* Entity;
    std::vector<Component*> AttachedComponents;
};

class ECS
{
public:

    ECS();
    ~ECS();

    template <typename Type, typename ... Args>
    Type* CreateEntity(Args&&... args);

    void Update();
    void FixedUpdate();
    void Draw();

    Entity* GetEntity(int index) { return mEntities[index]->Entity; }
    Entity* GetEntityByName(std::string name);
    template <typename T, typename... Args>
    T* AddComponent(Entity* entity, Args&&... args);
    template<typename T>
    T* GetComponent(Entity* entity);
    template<typename T>
    T* GetComponent(int entityIndex);
    template<typename T>
    bool HasComponent(int entityIndex) const;

    EC** GetEntities() { return mEntities; }
    int mEntityCount;
    int mEntityToAddCount;
    int mEntityToRemoveCount;
    std::map<int, std::list<Entity*>*> mEntitiesByLayer;
    std::map<std::string, int*> mEntitiesRegistry;
    bool IsEnable(int index);

    EC** mEntities = new EC*[16000];
private:
    EC** mToAddEntities = new EC*[1024];

    
    int** mToRemoveEntityIndex = new int*[512];
};

#include "ECS.inl"