#pragma once
#include "scripts/Script.h"

class RigidBody2D;

class PlayerMovement : public IScript
{
    
public:
    PlayerMovement() = default;
    PlayerMovement(Entity* camera);
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnCollisionEnter(Entity* other) override;
    void OnUpdate() override;
    void OnDisable() override;
    void SetHP(float hp) { m_hp = hp; }
    float GetHP() { return m_hp; }

    void Attack();

private:

    float m_hp;
    float m_time;
    float m_speed;
    float m_attackDelay;
    float m_attackDistance;

    sf::Vector2f m_direction;
    sf::Vector2f m_movement;
    sf::Vector2f movement;
    
    Entity* m_pCamera;
    TRANSFORM* m_transform;
    GameManager* m_pGameManager;
    RenderWindow* m_rw;
};
