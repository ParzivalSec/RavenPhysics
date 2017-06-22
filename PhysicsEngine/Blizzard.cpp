#include "Blizzard.h"
#include "World.h"
#include <gtx/matrix_transform_2d.hpp>

Blizzard::Blizzard(const glm::vec2& position, float strength,
	float spawnFrequency, raven::World& world)
	: m_sectors(32)
	, m_initialEmitDir({1, 0})
	, m_position(position)
	, m_strength(strength)
	, m_spawnFrequency(spawnFrequency)
	, m_emitAngleTotal(360.0f)
	, m_sectorAngle(0.0f)
	, m_currentEmitAngle(0.0f)
	, m_timeTillUpdate(m_spawnFrequency)
	, m_world(world)
{
	m_sectorAngle = m_emitAngleTotal / static_cast<float>(m_sectors);
}

void Blizzard::Update(float deltaTime)
{
	if (m_timeTillUpdate <= 0.0f)
	{
		// Calculate initial force for particle
		glm::vec2 force = glm::rotate(glm::mat3(1.0f), glm::radians(m_currentEmitAngle)) * glm::vec3(m_initialEmitDir, 0.0f);

		// Emit Particle in emitDirection
		raven::core::ResourceID id = m_world.AddParticle(m_position, {0, 0}, PARTICLE);
		raven::Particle* part = m_world.GetParticles().Lookup(id);
		part->velocity = force * m_strength;

		// Adjust next iteration emit direction
		m_currentEmitAngle += m_sectorAngle;
		
		if (m_currentEmitAngle > m_emitAngleTotal)
		{
			m_currentEmitAngle = 0.0f;
		}

		m_timeTillUpdate = m_spawnFrequency;
	}

	m_timeTillUpdate -= deltaTime;
}
