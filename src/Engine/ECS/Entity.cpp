#include "pch.h"

#include "ECS.h"
#include "Engine.h"
#include "Transform.h"
#include "scripts/ScriptManager.h"

int Entity::sNextId = 0;

Entity::Entity(int layer) : Bitmask(0), mCreated(false), m_destroyed(false), mId(sNextId), mIndex(0),
                   mTransform(new TRANSFORM(nullptr)), mLayer(layer), mName("Entity")
{
    mTag = Tag::NONE;
    mName.push_back(sNextId);
    sNextId++;
}

Entity::Entity(Entity* parent, int layer) : Bitmask(0),
                   mCreated(false), m_destroyed(false), mId(sNextId), mIndex(0),
                   mTransform(new TRANSFORM(parent)), mLayer(layer), mName("Entity")
{
    parent->GetTransform()->AddChild(this);
    mTag = Tag::NONE;
    mName.push_back(sNextId);
    sNextId++;
}

Entity::~Entity()
{
    delete mTransform;
}

void Entity::AddBitmask(int mask)
{
    Bitmask = Bitmask | mask;
}

void Entity::RemoveBitmask(int mask)
{
    Bitmask = Bitmask & ~(mask);
}

void Entity::SetIndex(int index)
{
    mIndex = index;
}

int Entity::GetId()
{
    return mId;
}

int* Entity::GetIndex()
{
    return &mIndex;
}

void Entity::Create(int index)
{
    mIndex = index;
    mCreated = true;
}

void Entity::Destroy()
{
    m_destroyed = true;
    for (auto child : GetTransform()->GetChildList())
    {
        child->Destroy();
    }
}

bool Entity::IsCreated() const
{
    return mCreated;
}

bool Entity::IsDestroyed() const
{
    return m_destroyed;
}

const char* Entity::GetStringFromTag(Tag oTag) const
{
    switch (oTag)
    {
        case Tag::NONE: return "NONE";
        case Tag::PLAYER: return "PLAYER";
        case Tag::GROUND: return "GROUND";
        case Tag::OBSTACLE: return "OBSTACLE";
        case Tag::ENEMY: return "ENEMY";
        case Tag::PROJECTILES: return "PROJECTILES";
        default: return "UNKNOWN";   
    }
}

Entity::Tag Entity::GetTagFromString(const std::string& oString) const
{
    if (oString == "NONE") return Tag::NONE;
    if (oString == "PLAYER") return Tag::PLAYER;
    if (oString == "GROUND") return Tag::GROUND;
    if (oString == "OBSTACLE") return Tag::OBSTACLE;
    if (oString == "ENEMY") return Tag::ENEMY;
    if (oString == "PROJECTILES") return Tag::PROJECTILES;

    return Tag::NONE;  // Valeur par défaut
}

bool Entity::IsEnable()
{
    return mEnabled;
}

void Entity::SetEnabled(bool state)
{
    mEnabled = state;
    for (auto child : GetTransform()->GetChildList())
    {
        child->SetEnabled(state);
    }
}
void Entity::SetName(const std::string& nName)
{
    auto nodeHandler = Engine::GetECS()->mEntitiesRegistry.extract(mName);
    nodeHandler.key() = nName;
    Engine::GetECS()->mEntitiesRegistry.insert(std::move(nodeHandler));
    mName = nName;
}
