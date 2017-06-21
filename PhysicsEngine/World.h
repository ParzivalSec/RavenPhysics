#pragma once

#include "PackedArray.h"
#include "Particle.h"
#include "GravityForceGenerator.h"
#include <vector>
#include "SpringJoint.h"
#include "AnchoredSpring.h"

namespace raven
{
	class World
	{
	public:

		explicit World(const WorldConfiguration& worldConfiguration);
		
		core::ResourceID AddParticle(glm::vec2 position, TYPE type);
		core::ResourceID AddParticle(glm::vec2 position, glm::vec2 acceleration, TYPE type);

		void AddSpringJoint(core::ResourceID particleOne, core::ResourceID particleTwo, float springC, float restL);
		void AddAnchoredSpring(core::ResourceID particle, const glm::vec2& anchor, float springC, float restL);

		core::PackedArray<Particle, 1000>& GetParticles(void) { return m_particles; }

		void Step(float deltaTime);

	protected:

		void Integrate(Particle& particle, float deltaTime);

	private:
		const WorldConfiguration& m_worldConfiguration;
	
		core::PackedArray<Particle, 1000> m_particles;

		std::vector<SpringJoint> m_springJoints;
		std::vector<AnchoredSpring> m_anchoredSprings;
		GravityForceGenerator m_gravity;
	};
}
