#pragma once
#include "scripts/Script.h"

class Experience : public IScript
{
public:
    Experience() = default;

    void OnTriggerStay(Entity* other) override;
    void OnStart() override;
    int GetValue();
    
private:
    int m_value;
};
