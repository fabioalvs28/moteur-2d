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

#include "scripts/PlayerMovement.h"
#include "scripts/WaveManager.h"

void TestScene::OnEnter()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Resources::instance().Initialize();
    
    player = ObjectFactory::CreateEntity<Entity>(1);
    player->SetName("player");
    player->GetTransform()->SetPosition(0.0f, 0.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().DEFAULT_SPRITE);
    //ObjectFactory::CreateComponent<AABBCollider>(player, 0.0f,0.0f,10.0f,10.0f);
    ObjectFactory::CreateComponent<CircleCollider>(player, 10.0f);
    player->SetTag(Entity::Tag::PLAYER);
    
    PlayerMovement* mov = ObjectFactory::AttachScript<PlayerMovement>(player);

    // Alexandre = ObjectFactory::CreateEntity<Entity>(2);
    // ObjectFactory::CreateComponent<CircleCollider>(Alexandre,50.0f);
    // ObjectFactory::CreateComponent<SpriteRenderer>(Alexandre, Resources::instance().ALEX_SPRITE);
    // Alexandre->SetName("Alexandre");
    // ObjectFactory::AttachScript<EnnemyMovement>(Alexandre);
    // ObjectFactory::AttachScript<EnnemyAttack>(Alexandre);

    // Entity* other = ObjectFactory::CreateEntity<Entity>(0);
    // other->GetTransform()->SetPosition(250.0f,250.0f);
    // ObjectFactory::CreateComponent<AABBCollider>(other, 0.0f,0.0f,100.0f,100.0f);
    // ObjectFactory::CreateComponent<SpriteRenderer>(other, Resources::instance().DEFAULT_SPRITE);
    // other->SetName("feur");
    //
    // //ObjectFactory::CreateComponent<CircleCollider>(other, 100.0f);
    // other->GetComponent<AABBCollider>()->SetTrigger(true);
    // //ObjectFactory::AttachScript<EnnemyMovement>(other, player);
    // //ObjectFactory::AttachScript<EnnemyAttack>(other);
    // //other->GetComponent<CircleCollider>()->SetStatic(true);
    //
    // Entity* other2 = ObjectFactory::CreateEntity<Entity>(0);
    // other2->GetTransform()->SetPosition(350.0f,350.0f);
    // ObjectFactory::CreateComponent<AABBCollider>(other2, 0.0f,0.0f,100.0f,100.0f);
    // //ObjectFactory::CreateComponent<CircleCollider>(other2, 100.0f);
    // //other2->GetComponent<CircleCollider>()->SetStatic(true);
    // other2->GetComponent<AABBCollider>()->SetStatic(true);
    //
    camera = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Camera>(camera);
    camera->SetName("camera");

    
}

void TestScene::OnLoad()
{
    Bat = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::AttachScript<WaveManager>(Bat);
}

void TestScene::OnUpdate()
{
    camera->GetTransform()->SetPosition(player->GetTransform()->position.x - Engine::GetRenderWindow()->getSize().x * 0.5f, player->GetTransform()->position.y - Engine::GetRenderWindow()->getSize().y * 0.5f);
}




