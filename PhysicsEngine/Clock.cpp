#include "Clock.h"

using namespace raven;

void Clock::Start()
{
	m_startPoint = high_resolution_clock::now();
}

const duration<float> Clock::GetElapsedTime() const
{
	high_resolution_clock::time_point currentTime = high_resolution_clock::now();
	return duration_cast<duration<float>>(currentTime - m_startPoint);
}
