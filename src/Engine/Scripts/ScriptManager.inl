#include "ScriptManager.h"
#pragma once

template <typename SType, typename ... Args>
SType* ScriptManager::CreateScript(Entity* entity, Args&&... args)
{
    SType* script = new SType(std::forward<Args>(args)...);
    script->SetOwner(entity);
    scriptedEntityToAdd[entity->GetIndex()].push_back(script);
    return script;
}

template<typename S>
inline S* ScriptManager::GetScript(Entity* pEntity)
{
    std::vector<IScript*> scripts;
    if (pEntity->IsCreated())
        scripts = scriptedEntity[pEntity->GetIndex()];
    else
        scripts = scriptedEntityToAdd[pEntity->GetIndex()];

    for (int i = 0; i < scripts.size(); i++)
    {
        if (S* foundScript = dynamic_cast<S*>(scripts[i]))
        {
            return foundScript;
        }
    }
    return nullptr;
}