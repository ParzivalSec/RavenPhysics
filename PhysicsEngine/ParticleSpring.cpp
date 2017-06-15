#include "ParticleSpring.h"

#include <geometric.hpp>
#include "Particle.h"

using namespace raven;

ParticleSpring::ParticleSpring(Particle* other, float springConstant, float restLength)
	: m_other(other)
	, m_springConstant(springConstant)
	, m_restLength(restLength)
{
	assert(m_other != nullptr && "Other Particle is not allowed to be nullptr");
}

void ParticleSpring::UpdateForce(Particle& particle, float deltaTime)
{
	// Calculate spring vector
	glm::vec2 force = particle.GetPosition();
	force -= m_other->GetPosition();

	// Calculate magnitude of force
	float magnitude = glm::length(force);
	magnitude = glm::abs(magnitude - m_restLength);
	magnitude *= m_springConstant;

	// Calculate the final spring force to apply
	force = glm::normalize(force);
	force *= -magnitude;
	particle.ApplyForce(force);
}

ParticleSpring::~ParticleSpring() {}
