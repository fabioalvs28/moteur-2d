#include "pch.h"
#include "GameTimer.h"

GameTimer::GameTimer(): timeScale(1.0f), m_isPaused(false)
{
	mLastFrameTime = std::chrono::high_resolution_clock::now();
}

float GameTimer::GetDeltaTime() const
{
	if(!m_isPaused)
		return (mDeltaTime / 1000000000.0f) * timeScale;

	return 0.0f;
}

float GameTimer::GetFixedDeltaTime() const
{
	if(!m_isPaused)
		return 1.0f/60.0f * timeScale;

	return 0.0f;
}

void GameTimer::UpdateTime()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	mDeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - mLastFrameTime).count();
	mLastFrameTime = currentTime;
}

float GameTimer::GetFPS()
{
	return 1.0f / GetDeltaTime();
}

void GameTimer::SetTimeScale(float scale)
{
	timeScale = scale;
}
