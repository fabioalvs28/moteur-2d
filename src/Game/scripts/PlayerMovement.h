#pragma once
#include "scripts/Script.h"

class ProgressBar;
class RigidBody2D;

class PlayerMovement : public IScript
{
public:
    PlayerMovement() = default;
    PlayerMovement(Entity* pCamera);
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnCollisionEnter(Entity* other) override;
    void OnUpdate() override;
    void OnDisable() override;
    void Attack();
    void LevelUp();

    void TakeDamage(float damage); 

private:

    float m_time;
    float m_attackDelay;
    float m_attackDistance;
    float m_speed;
    float m_hp;
    float m_maxHp;
    int m_experience;
    int m_maxExp;
    
    sf::Vector2f m_direction;
    sf::Vector2f m_movement;

    Entity* m_pCamera;
    TRANSFORM* m_pTransform;
    GameManager* m_pGameManager;
    RenderWindow* m_rw;

    //UI
    ProgressBar* m_pExpBar;
    ProgressBar* m_pHealthBar;
};
