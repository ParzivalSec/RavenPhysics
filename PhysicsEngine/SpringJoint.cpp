#include "SpringJoint.h"
#include "World.h"

#include <geometric.hpp>

using namespace raven;

SpringJoint::SpringJoint(float springConstant, float restLength)
	: m_particles{0}
	, m_springConstant(springConstant)
	, m_restLength(restLength)
{}

SpringJoint::SpringJoint(core::ResourceID particle, core::ResourceID other, float springConstant, float restLength)
	: m_particles{ particle, other }
	, m_springConstant(springConstant)
	, m_restLength(restLength)
{}

void SpringJoint::AddParticle(core::ResourceID particle)
{
	// TODO: Be implemented
}

void SpringJoint::UpdateForce(float deltaTime, World& world)
{
	Particle* particleOne = world.GetParticles().Lookup(m_particles[0]);
	Particle* particleTwo = world.GetParticles().Lookup(m_particles[1]);

	glm::vec2 force = particleOne->position;
	force -= particleTwo->position;

	float magnitude = glm::length(force);
	magnitude = glm::abs(magnitude - m_restLength);
	magnitude *= m_springConstant;

	force = glm::normalize(force);
	force *= -magnitude;
	particleOne->forceAccumulator += force * 0.5f;
	particleTwo->forceAccumulator += -force * 0.5f;
}