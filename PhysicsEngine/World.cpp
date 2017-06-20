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

void World::Step(float deltaTime)
{
	for(size_t i = 0; i < m_particles.Size(); i++)
	{
		Particle& particle = m_particles[i];

		// Apply gravity
		m_gravity.ApplyForceTo(particle);

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
