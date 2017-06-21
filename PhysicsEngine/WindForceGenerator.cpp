#include "WindForceGenerator.h"
#include "Particle.h"

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

void WindForceGenerator::ToggleState(void)
{
	m_active = !m_active;
}

void WindForceGenerator::UpdateForce(float deltaTime, Particle* particle)
{
	if (!m_active) return;

	assert(particle != nullptr);

	particle->forceAccumulator += m_direction * m_windStrength;
}