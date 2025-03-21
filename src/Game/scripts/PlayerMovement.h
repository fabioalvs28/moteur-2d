#pragma once
#include "scripts/Script.h"

class RigidBody2D;

class PlayerMovement : public IScript
{
    
public:
    PlayerMovement() = default;
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;

private:
    void Attack();

private:
    bool m_isAttacking;

    float m_time;
    float m_attackTime;
    float m_attackDelay;
    float m_attackDuration;
    float m_attackDistance;
    float m_speed;
    GameManager* m_pGameManager;
    float velocity = 1.0f;
    RenderWindow* m_rw;
    sf::Vector2f m_direction;
    sf::Vector2f m_movement;
};
