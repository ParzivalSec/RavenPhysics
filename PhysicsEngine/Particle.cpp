#include "Particle.h"
#include <gtc/functions.hpp>


using namespace raven;

Particle::Particle(glm::vec2 initialPosition, glm::vec2 initialVelocity)
	: m_position(initialPosition)
	, m_velocity(initialVelocity)
	, m_acceleration({0, 0})
	, m_forceAccum({0, 0})
	, m_damping(0.99f)
	, m_inverseMass(0.0f)
{}

void Particle::Integrate(float deltaTime)
{
	if (m_inverseMass <= 0.0f) return;

	assert(deltaTime > 0.0f);

	// Update linear position of particle
	m_position += m_velocity * deltaTime;

	// Calculate the actual acceleration (later add forces)
	glm::vec2 resAcceleration = m_acceleration;
	resAcceleration += m_forceAccum * m_inverseMass;

	// Update linear velocity
	m_velocity += resAcceleration * deltaTime;

	// Impose the drag
	m_velocity *= glm::pow(m_damping, deltaTime);

	// Clear the forces
	ClearAccumulator();
}

void Particle::ClearAccumulator()
{
	m_forceAccum = { 0, 0 };
}

void Particle::ApplyForce(const glm::vec2& force)
{
	m_forceAccum += force;
}
