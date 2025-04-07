#pragma once
#include "scripts/script.h"
#include "Engine/Scripts/ScriptRegistry.h"

class LevelUpMenu : public IScript
{
public:
    void OnStart() override {};
    void OnUpdate() override {};

    bool IsButtonClicked();
private:
    Entity* m_background;
    Entity* m_button1;
    Entity* m_button2;
    Entity* m_button3;
};

REGISTER_SCRIPT(LevelUpMenu)