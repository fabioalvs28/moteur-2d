#pragma once
#include "Component.h"
#include "Render/SpriteSheet.h"

class Texture;
class Animator : public Component
{
public:
	static constexpr int BITMASK = 1 << 11;

	Animator(Entity* entity, SpriteSheet* pSpriteSheet, float timeBetween);
	~Animator() override;

	void SetAnimation(const char* pathToSpriteSheet, int startX, int startY, int singleWidth, int singleHeight, int width = 1, int height = 1, float timeBetween = 1);

	SpriteSheet* mp_SpriteSheet = nullptr;

	bool m_isExtract = false;
	int m_startX;
	int m_startY;
	int m_singleWidth;
	int m_singleHeight;
	int m_width;
	int m_height;
	
	float m_timeBetween = 0;
	float m_elapsedTime = 0;

	float m_actualIndex = 0;

	Texture* mp_texture = nullptr;

	int GetBitmask() override;
	void Serialize(json& json) override {}
	void Deserialize(json& json) override {}
};

