#pragma once
#include "scripts/Script.h"

class WaveManager : public IScript
{
public:
    WaveManager() = default;

    void OnStart() override;
    void SpawnEnnemy(std::string prefab, float TimeBetweenSpawn); 
    void OnUpdate() override;
    sf::Vector2f GenerateSpawnPosition();
    void Decrease() { mEntityCount -= 1; }
private:
    float mTimer;
    float mTimerBetweenSpawn;
    TRANSFORM* Player;
    int mEntityCount;
    int mMaxEntityCount;
};

