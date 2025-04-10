#include "pch.h"
#include "TestScene.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "ECS/Components/Colliders/CircleCollider.h"
#include "scripts/EnnemyAttack.h"
#include "scripts/EnnemyMovement.h"
#include "scripts/LevelUpMenu.h"
#include "scripts/MusicScript.h"
#include "scripts/PlayerAttack.h"

#include "scripts/PlayerMovement.h"
#include "scripts/WaveManager.h"
#include "scripts/WeaponContainer.h"
#include "scripts/Weapons/Sword.h"
#include "scripts/Weapons/Weapon.h"

void TestScene::OnEnter()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    camera = ObjectFactory::CreateEntity<Entity>();
    Camera* cam = ObjectFactory::CreateComponent<Camera>(camera);
    camera->SetName("camera");
    Resources::instance().Initialize();
    
    player = ObjectFactory::CreateEntity<Entity>(1);
    player->SetName("player");
    player->GetTransform()->SetPosition(0.0f, 0.0f);
    SpriteRenderer* sr = ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().PETER);
    //ObjectFactory::CreateComponent<AABBCollider>(player, 0.0f,0.0f,10.0f,10.0f);
    ObjectFactory::CreateComponent<CircleCollider>(player, 10.0f);
    MusicScript * ms =ObjectFactory::AttachScript<MusicScript>(player);
    PlayerMovement* mov = ObjectFactory::AttachScript<PlayerMovement>(player);
    ObjectFactory::AttachScript<WeaponContainer>(player);
    player->SetTag(Entity::Tag::PLAYER);
    
    PlayerAttack* pat = ObjectFactory::AttachScript<PlayerAttack>(player);
    Sword* sword = ObjectFactory::AttachScript<Sword>(player);
    pat->AddWeapon(sword);
    ObjectFactory::AttachScript<LevelUpMenu>(player);
    ms->AddMusic(0, "../../res/Peter's Song.mp3");
    ms->AddSound("HurtSound1", "../../res/SoundEffects/HurtSound.wav");
    ms->AddSound("HurtSound2", "../../res/SoundEffects/HurtSound2.wav");
    ms->PlayMusic(0);

    camera = ObjectFactory::CreateEntity<Entity>();
    Camera* cam = ObjectFactory::CreateComponent<Camera>(camera);
    camera->SetName("camera");
    

    Bat = ObjectFactory::CreateEntity<Entity>();
    Bat->SetName("WaveManager");
    
}

void TestScene::OnLoad()
{
    ObjectFactory::AttachScript<WaveManager>(Bat);
}

void TestScene::OnUpdate()
{
}




