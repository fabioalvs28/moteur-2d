#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include "ScriptManager.h"

struct IScript;

std::unordered_map<std::string, std::function<IScript*()>>& GetScriptRegistry();

#define REGISTER_SCRIPT(ScriptClass) \
    static struct ScriptClass##_Register { \
        ScriptClass##_Register() { \
            GetScriptRegistry()[#ScriptClass] = []() { return new ScriptClass(); }; \
            Engine::GetScriptManager()->RegisterScript(#ScriptClass, new ScriptClass()); \
        } \
    } ScriptClass##_register;