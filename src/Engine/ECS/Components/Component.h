#pragma once

class Entity;

class Component
{
public:
    Component(Entity* entity);
    virtual ~Component() = default;
    Entity* GetEntity() const;

    void Activate();
    void Deactivate();
    bool GetState() const;
    const char* GetTypeName() const;
    virtual int GetBitmask() = 0;
    virtual void Serialize(json& json) = 0;
    virtual void Deserialize(json& json) = 0;

protected:
    Entity* mEntity;
    bool mActive;
};
