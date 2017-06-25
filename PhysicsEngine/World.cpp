#include "World.h"

#include <geometric.hpp>
#include "Manifold.h"
#include "ScenereyManifold.h"

#include "CollisionDetection.h"
#include "CollisionResolver.h"

#include <intrin.h>

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

	m_particleHandles.push_back(newParticle);
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

WindForceGenerator& World::AddWindForceGenerator(const glm::vec2& position, const glm::vec2& direction, float windStrength)
{
	m_windForceGenerator.push_back({position, direction, windStrength});
	return m_windForceGenerator.back();
}

StaticBox& World::AddStaticBox(const glm::vec2& position, const glm::vec2& extend, float rotation)
{
	m_scenery.push_back({ position, extend.x, extend.y, rotation });
	return m_scenery.back();
}

void World::AddSpringJoint(core::ResourceID particleOne, core::ResourceID particleTwo, float springC, float restL)
{
	m_springJoints.push_back({ particleOne, particleTwo, springC, restL });
}

void World::Step(float deltaTime)
{
	for (size_t s = 0; s < m_springJoints.size(); s++)
	{
		m_springJoints[s].UpdateForce(deltaTime, *this);
	}

	for (size_t s = 0; s < m_anchoredSprings.size(); s++)
	{
		m_anchoredSprings[s].UpdateForce(deltaTime, *this);
	}

	for(size_t i = 0; i < m_particles.Size(); i++)
	{
		Particle& particle = m_particles[i];

		// Apply gravity
		m_gravity.ApplyForceTo(particle);

		for (size_t s = 0; s < m_windForceGenerator.size(); s++)
		{
			m_windForceGenerator[s].UpdateForce(deltaTime, &particle);
		}

		Integrate(particle, deltaTime);
	}

	ResolveCollisions();
	CheckLifetime(deltaTime);
}

void World::CheckLifetime(float deltaTime)
{
	for (size_t i = 0; i < m_particleHandles.size(); i++)
	{
		Particle* particle = m_particles.Lookup(m_particleHandles[i]);

		if (particle->lifeTime <= 0.0f)
		{
			m_particles.Remove(m_particleHandles[i]);
			m_particleHandles.erase(m_particleHandles.begin() + i);
		}

		if (particle->type == PARTICLE)
		{
			particle->lifeTime -= deltaTime;
		}
	}
}

void World::ResolveCollisions()
{
	// Repeat for collisionIteration times

		// Check collisions among particles
			// SphereSphere collisions between BODY particles - resolve positions
			// PointShere collisions for PARTICLE particles - kill snowflake
	for (size_t it = 0; it < m_worldConfiguration.collisionIterations; it++)
	{
		std::vector<Manifold> manifolds;
		for (size_t i = 0; i < m_particles.Size(); i++)
		{
			for (size_t j = 0; j < m_particles.Size(); j++)
			{
				if (&m_particles[i] == &m_particles[j])
				{
					continue;
				}

				if (m_particles[i].type == BODY && m_particles[j].type == BODY)
				{
					Manifold manifold(m_particles[i], m_particles[j]);

					if (coll::CircleCicle(manifold))
					{
						manifolds.push_back(manifold);
					}
				}
				
				if (m_particles[i].type + m_particles[j].type == 1)
				{
					Particle& part = m_particles[i].type == PARTICLE ? m_particles[i] : m_particles[j];
					Particle& body = m_particles[j].type == BODY ? m_particles[j] : m_particles[i];

					Manifold manifold(part, body);

					if (coll::PointCircle(manifold))
					{
						part.lifeTime = 0.0f;
					}
				}
			}
		}

		for (size_t i = 0; i < manifolds.size(); i++)
		{
			coll::ResolveCollision(manifolds[i]);
		}

		std::vector<SceneryManifold> sceneManifolds;
		for (size_t i = 0; i < m_particles.Size(); i++)
		{
			for (size_t j = 0; j < m_scenery.size(); j++)
			{
				SceneryManifold manifold(m_particles[i], m_scenery[j]);

				if (m_scenery[j].GetRotation() == 0)
				{
					if (coll::CircleAABB(manifold))
					{
						sceneManifolds.push_back(manifold);
					}
				}
				else
				{
					if (coll::CircleOOBB(manifold))
					{
						sceneManifolds.push_back(manifold);
					}
				}
			}
		}

		for (size_t i = 0; i < sceneManifolds.size(); i++)
		{
			coll::ResolveStaticCollision(sceneManifolds[i]);
		}
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
	//particle.acceleration = { 0, 0 };
}
