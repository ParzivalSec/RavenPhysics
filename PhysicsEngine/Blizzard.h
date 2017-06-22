#pragma once

#include <vec2.hpp>

namespace raven
{
	class World;
}

class Blizzard
{
public:
	Blizzard(const glm::vec2& position, float strength, float spawnFrequency, raven::World& world);

	void Update(float deltaTime);
	
private:
	uint32_t m_sectors;

	glm::vec2 m_initialEmitDir;
	glm::vec2 m_position;

	float m_strength;
	float m_spawnFrequency;
	float m_emitAngleTotal;
	float m_sectorAngle;
	float m_currentEmitAngle;

	float m_timeTillUpdate;

	raven::World& m_world;
};
