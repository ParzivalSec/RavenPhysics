#include "WindForceGenerator.h"
#include "Particle.h"
#include <detail/func_geometric.inl>

using namespace raven;

WindForceGenerator::WindForceGenerator(const glm::vec2 position, const glm::vec2& direction, float strength)
	: m_active(true)
	, m_windStrength(strength)
	, m_position(position)
	, m_direction(direction)
{}

const glm::vec2& WindForceGenerator::GetPosition() const
{
	return m_position;
}

const glm::vec2& WindForceGenerator::GetDirection() const
{
	return m_direction;
}

void WindForceGenerator::SetStrength(float strength)
{
	m_windStrength = strength;
}

void WindForceGenerator::SetBounds(const glm::vec2& bounds)
{
	m_lower_upperBounds = bounds;
}

void WindForceGenerator::SetDistance(float distance)
{
	m_maxDistance = distance;
}

void WindForceGenerator::ToggleState(void)
{
	m_active = !m_active;
}

void WindForceGenerator::UpdateForce(float deltaTime, Particle* particle)
{
	if (!m_active) return;

	assert(particle != nullptr);

	if (particle->position.y <= m_lower_upperBounds.y && particle->position.y >= m_lower_upperBounds.x && particle->position.x < m_position.x)
	{
		float distance = glm::length(particle->position - m_position);
		float fallOffStrength = m_windStrength;

		particle->forceAccumulator += m_direction * fallOffStrength;
	}
}