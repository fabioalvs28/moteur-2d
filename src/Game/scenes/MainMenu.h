#pragma once
#include "ECS/Entity.h"
#include "Managers/Scene.h"

class MainScene: public Scene
{


private:
    void OnEnter() override;
    void OnExit() override {}
    void OnFixedUpdate() override {}
    void Render() override {}
    void OnUpdate() override {};
    void OnLoad() override;

};
