#include "pch.h"
#include "Animator.h"
#include "Render/Texture.h"

Animator::Animator(Entity* entity, SpriteSheet* pSpriteSheet, float timeBetween)
: Component(entity)
{
    mp_SpriteSheet = pSpriteSheet;

    //m_startX = startX;
    //m_startY = startY;
    m_singleWidth = pSpriteSheet->GetSize().x;
    m_singleHeight = pSpriteSheet->GetSize().y;
    m_width = pSpriteSheet->GetTotalSize().x;
    m_height = pSpriteSheet->GetTotalSize().y;

    m_timeBetween = timeBetween;

    //mp_SpriteSheet->Extract(m_startX, m_startY, m_singleWidth, m_singleHeight, m_width, m_height);
    //
    //if (mp_texture)
    //{
    //    delete mp_texture;
    //    mp_texture = nullptr;
    //}
}

Animator::~Animator()
{

}

void Animator::SetAnimation(const char* pathToSpriteSheet, int startX, int startY, int singleWidth, int singleHeight, int width, int height, float timeBetween)
{

    if (mp_SpriteSheet)
    {
        delete mp_SpriteSheet;
        mp_SpriteSheet = nullptr;
    }

    if (mp_texture)
    {
        delete mp_texture;
        mp_texture = nullptr;
    }

    mp_texture = new Texture(pathToSpriteSheet);
    mp_SpriteSheet = new SpriteSheet(*mp_texture);

    m_startX = startX;
    m_startY = startY;
    m_singleWidth = singleWidth;
    m_singleHeight = singleHeight;
    m_width = width;
    m_height = height;
    m_actualIndex = 0;
    m_elapsedTime = 0;

    mp_SpriteSheet->Extract(m_startX, m_startY, m_singleWidth, m_singleHeight, m_width, m_height);
    mp_SpriteSheet->SetSprite(m_actualIndex);

    m_timeBetween = timeBetween;
    
}

int Animator::GetBitmask()
{
    return BITMASK;
}
