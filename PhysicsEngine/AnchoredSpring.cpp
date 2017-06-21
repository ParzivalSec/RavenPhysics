#include "AnchoredSpring.h"
#include "Particle.h"
#include "World.h"

#include <geometric.hpp>

using namespace raven;

AnchoredSpring::AnchoredSpring(float springConstant, float restLength)
	: m_particle(0)
	, m_anchor({0, 0})
	, m_springConstant(springConstant)
	, m_restLength(restLength)
{}

AnchoredSpring::AnchoredSpring(const glm::vec2& anchor, core::ResourceID particle, float springConstant, float restLength) 
	: m_particle(particle)
	, m_anchor(anchor)
	, m_springConstant(springConstant)
	, m_restLength(restLength) 
{}

void AnchoredSpring::AddParticle(core::ResourceID particle)
{
	m_particle = particle;
}


void AnchoredSpring::SetAnchor(const glm::vec2 anchor)
{
	m_anchor = anchor;
}


void AnchoredSpring::UpdateForce(float deltaTime, World& world)
{
	Particle* particle = world.GetParticles().Lookup(m_particle);

	glm::vec2 force = particle->position;
	force -= m_anchor;

	float magnitude = glm::length(force);
	magnitude = (m_restLength - magnitude) * m_springConstant;

	force = glm::normalize(force);
	force *= -magnitude;
	particle->forceAccumulator += -force;
}
