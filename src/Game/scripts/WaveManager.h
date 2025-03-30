#pragma once
#include "Wave.h"
#include "scenes/LevelScene.h"
#include "scripts/Script.h"

class WaveManager : public IScript
{
public:
    WaveManager(Scene* currentScene);
    void OnUpdate() override;
    void SpawnEnnemiesBasedOnTime(float time);

private:
    float mElapsedTime;
    LevelScene* mpCurrentScene;
    
};
