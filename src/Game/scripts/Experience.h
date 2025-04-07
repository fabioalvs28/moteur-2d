#pragma once
#include "scripts/Script.h"

class Experience : public IScript
{
public:
    Experience() = default;

    void OnTriggerEnter(Entity* other) override;
    void OnStart() override;
    void OnUpdate() override;
    int GetValue();
    
private:
    sf::Vector2f position;
    int m_value;
};
