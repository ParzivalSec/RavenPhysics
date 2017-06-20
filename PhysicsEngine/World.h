#pragma once

#include "PackedArray.h"
#include "Particle.h"
#include "GravityForceGenerator.h"

namespace raven
{
	class World
	{
	public:

		explicit World(const WorldConfiguration& worldConfiguration);
		
		core::ResourceID AddParticle(glm::vec2 position, TYPE type);
		core::ResourceID AddParticle(glm::vec2 position, glm::vec2 acceleration, TYPE type);

		const core::PackedArray<Particle, 1000>& GetParticles(void) const { return m_particles; }

		void Step(float deltaTime);

	protected:

		void Integrate(Particle& particle, float deltaTime);

	private:
		const WorldConfiguration& m_worldConfiguration;
	
		core::PackedArray<Particle, 1000> m_particles;
		GravityForceGenerator m_gravity;
	};
}
