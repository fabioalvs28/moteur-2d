#pragma once

#include "Engine.h"
#include "ECS.h"
#include "Scripts/ScriptManager.h"

template <typename T>
T* Entity::GetComponent()
{
    return Engine::GetECS()->GetComponent<T>(this);
}

template <typename T>
bool Entity::HasComponent() const
{
    static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
    if (Bitmask & T::BITMASK) return true;
    return false;
}

template <typename T>
T* Entity::GetScript()
{
    static_assert(std::is_base_of<IScript, T>::value, "T must be a subclass of Iscript");
    
    for(int i = 0; i < Engine::GetScriptManager()->scriptedEntity[this->GetIndex()].size(); i++)
    {
        if(T* foundScript = dynamic_cast<T*>(Engine::GetScriptManager()->scriptedEntity[this->GetIndex()][i]))
        {
            return foundScript;
        }
    }

    return nullptr;
}
