#include "pch.h"
#include "WaveManager.h"

#include "ObjectFactory.h"
#include "scenes/LevelScene.h"

WaveManager::WaveManager(LevelScene* currentScene) : mElapsedTime(0.0f), mpCurrentScene(currentScene)
{
    
}

void WaveManager::OnUpdate()
{
    mElapsedTime += Engine::GetDeltaTime();
    SpawnEnnemiesBasedOnTime(mElapsedTime);
}

void WaveManager::SpawnEnnemiesBasedOnTime(float time)
{
    if(time < 300)
    {
        SpawnEnnemies(Bats);
    }
}

void WaveManager::SpawnEnnemies(Entity* EnnemyToSpawn)
{
    mpCurrentScene.
    
}