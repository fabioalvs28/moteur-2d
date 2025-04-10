#pragma once
#include "LevelUpMenu.h"
#include "MusicScript.h"
#include "scripts/Script.h"

class ProgressBar;
class RigidBody2D;
#include "Engine/Scripts/ScriptRegistry.h"

class PlayerMovement : public IScript
{
public:
    PlayerMovement() = default;
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnCollisionEnter(Entity* other) override;
    void OnUpdate() override;
    void OnDisable() override;
    void LevelUp();
    sf::Vector2f GetDirection() const { return m_direction; }
    void TakeDamage(float damage); 

private:
    void Die();

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
    LevelUpMenu* mp_LevelUpMenu;
    //UI
    ProgressBar* m_pExpBar;
    ProgressBar* m_pHealthBar;

    MusicScript* mp_MusicScript;
    friend LevelUpMenu;
};

REGISTER_SCRIPT(PlayerMovement)