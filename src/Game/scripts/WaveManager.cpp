#include "pch.h"
#include "WaveManager.h"

#include "ObjectFactory.h"

void WaveManager::OnStart()
{
    Player = Engine::GetEntityByName("player")->GetTransform();
    mMaxEntityCount = 5;
}

void WaveManager::SpawnEnnemy(std::string prefab, float TimeBetweenSpawn)
{
    if(mEntityCount < mMaxEntityCount)
    {
        mTimerBetweenSpawn += Engine::GetDeltaTime();
    
        if(mTimerBetweenSpawn >= TimeBetweenSpawn)
        {
            Entity* temp = ObjectFactory::LoadPrefab(prefab);
            temp->GetTransform()->SetPosition(GenerateSpawnPosition());
            mEntityCount++;
            mTimerBetweenSpawn = 0.0f;
        }
    }
}

void WaveManager::OnUpdate()
{
    mTimer += Engine::GetDeltaTime();

    if(mTimer >= 1.0f)
    {
        SpawnEnnemy("Alexandre.prefab", 0.1f);
    }
    
}

sf::Vector2f WaveManager::GenerateSpawnPosition()
{
    sf::Vector2f spawnPos;
    sf::Vector2f pos = Player->position;
    float camWidth = Engine::GetRenderWindow()->getSize().x;
    float camHeight = Engine::GetRenderWindow()->getSize().y;
    float buffer = 150.0f;
    int side = rand() % 4;

    switch(side)
    {
    case 0: // Gauche
        spawnPos.x = pos.x - camWidth / 2 - buffer;
        spawnPos.y = pos.y + (rand() % (int)camHeight) - camHeight / 2 + buffer;
        break;
    case 1: // Droite
        spawnPos.x = pos.x + camWidth / 2 + buffer;
        spawnPos.y = pos.y + (rand() % (int)camHeight) + camHeight / 2 + buffer;
        break;
    case 2: // Haut
        spawnPos.y = pos.y + camHeight / 2 + buffer;
        spawnPos.x = pos.x + (rand() % (int)camWidth) - camWidth / 2 + buffer;
        break;
    case 3: // Bas
        spawnPos.y = pos.y - camHeight / 2 - buffer;
        spawnPos.x = pos.x + (rand() % (int)camWidth) - camWidth / 2 + buffer;
        break;
    }

    return spawnPos;
}
