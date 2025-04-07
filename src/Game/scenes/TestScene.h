#pragma once
#include "ECS/Entity.h"
#include "Managers/Scene.h"

class TestScene: public Scene
{
    Entity* player;
    Entity* camera;
    Entity* Bat;
    Entity* Alexandre;
private:
    void OnEnter() override;
    void OnExit() override {}
    void OnFixedUpdate() override {}
    void Render() override {}
    void OnUpdate() override;
    void OnLoad() override;

};
