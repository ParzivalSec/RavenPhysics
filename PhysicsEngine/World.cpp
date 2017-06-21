#include "World.h"

#include <geometric.hpp>

using namespace raven;

World::World(const WorldConfiguration& worldConfiguration)
	: m_worldConfiguration(worldConfiguration)
	, m_gravity(worldConfiguration)
{}

core::ResourceID World::AddParticle(glm::vec2 position, TYPE type)
{
	core::ResourceID newParticle = m_particles.Add();
	Particle* realParticle = m_particles.Lookup(newParticle);

	realParticle->position = position;
	realParticle->type = type;

	return newParticle;
}

core::ResourceID World::AddParticle(glm::vec2 position, glm::vec2 acceleration, TYPE type)
{
	core::ResourceID newParticle = AddParticle(position, type);
	Particle* realParticle = m_particles.Lookup(newParticle);

	realParticle->acceleration = acceleration;

	return newParticle;
}

void World::AddAnchoredSpring(core::ResourceID particle, const glm::vec2& anchor, float springC, float restL)
{
	m_anchoredSprings.push_back({anchor, particle, springC, restL});
}

void World::AddSpringJoint(core::ResourceID particleOne, core::ResourceID particleTwo, float springC, float restL)
{
	m_springJoints.push_back({ particleOne, particleTwo, springC, restL });
}

void World::Step(float deltaTime)
{
	for(size_t i = 0; i < m_particles.Size(); i++)
	{
		Particle& particle = m_particles[i];

		// Apply gravity
		m_gravity.ApplyForceTo(particle);
		
		for (size_t s = 0; s < m_springJoints.size(); s++)
		{
			m_springJoints[s].UpdateForce(deltaTime, *this);
		}

		for (size_t s = 0; s < m_anchoredSprings.size(); s++)
		{
			m_anchoredSprings[s].UpdateForce(deltaTime, *this);
		}

		Integrate(particle, deltaTime);
	}
}

void World::Integrate(Particle& particle, float deltaTime)
{
	if (particle.inverseMass <= 0.0f) return;

	assert(deltaTime > 0.0f);

	// Update linear position of particle
	particle.position += particle.velocity * deltaTime;

	// Calculate the actual acceleration (later add forces)
	glm::vec2 resAcceleration = particle.acceleration;
	resAcceleration += particle.forceAccumulator * particle.inverseMass;

	// Update linear velocity
	particle.velocity += resAcceleration * deltaTime;

	// Impose the drag
	particle.velocity *= glm::pow(particle.damping, deltaTime);

	// Clear the forces
	particle.forceAccumulator = { 0, 0 };
}
