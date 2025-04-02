#include "pch.h"
#include "ScriptRegistry.h"

std::unordered_map<std::string, std::function<IScript*()>>& GetScriptRegistry()
{
    static std::unordered_map<std::string, std::function<IScript*()>> registry;
    return registry;
}