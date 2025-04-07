#pragma once
#include <cstdint>

struct TRANSFORM;

class Entity
{
public:
    Entity(int layer = 0);
    Entity(Entity* parent, int layer = 0);
    ~Entity();
    bool IsEnable();
    void SetEnabled(bool enable);

    
    enum class Tag : uint8_t
    {
        NONE,
        PLAYER,
        GROUND,
        OBSTACLE,
        ENEMY,
        PROJECTILES,
        XP,

        TAG_COUNT
    };

    
    template<typename T>
    T* GetComponent();

    template<typename S>
    S* GetScript();

    template<typename T>
    bool HasComponent() const;

    void AddBitmask(int mask);
    void RemoveBitmask(int mask);
    void SetIndex(int index);
    int GetId();
    int* GetIndex();

    void Create(int index);
    void Destroy();

    bool IsCreated() const;
    bool IsDestroyed() const;
    
    void SetTag(Tag nTag) { mTag = nTag; }
    bool IsTag(Tag oTag) const { return mTag == oTag; }
    [[nodiscard]] Tag GetTag() const { return mTag; }

    const char* GetStringFromTag(Tag oTag) const;
    Tag GetTagFromString(const std::string& oString) const;
    
    int GetLayer() const { return mLayer; }
    void SetLayer(int nLayer) { mLayer = nLayer; }
    
    TRANSFORM* GetTransform() const {return mTransform; }
    int Bitmask;
    
    std::string GetName() const { return mName;}
    void SetName(const std::string& nName);
    
protected:
    bool mEnabled;
    bool mCreated;
    bool m_destroyed;
    int mId;
    int mIndex;
    int mLayer;
    Tag mTag;
    std::string mName;
    
private:
    TRANSFORM* mTransform;
    static int sNextId;
};

#include "Entity.inl"