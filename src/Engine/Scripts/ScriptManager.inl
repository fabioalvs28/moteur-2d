#pragma once

#include "Utils/CoreUtils.h"

template <typename SType, typename ... Args>
SType* ScriptManager::CreateScript(Entity* entity, Args&&... args)
{
    static_assert(std::is_base_of<IScript, SType>::value, "T must be a subclass of IScript");
    SType* script = new SType(std::forward<Args>(args)...);
    std::string name = CoreUtils::type(*script);
    mScriptRegistry[name] = script;
    script->SetOwner(entity);
    scriptedEntityToAdd[entity->GetIndex()].push_back(script);
    return script;
}
