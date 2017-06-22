#pragma once

#include "PackedArray.h"
#include "Particle.h"
#include "GravityForceGenerator.h"
#include <vector>
#include "SpringJoint.h"
#include "AnchoredSpring.h"
#include "WindForceGenerator.h"
#include "StaticBox.h"

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
		void AddWindForceGenerator(const glm::vec2& position, const glm::vec2& direction, float windStrength);
		void AddStaticBox(const glm::vec2& position, const glm::vec2& extend, float rotation);

		core::PackedArray<Particle, 5000>& GetParticles(void) { return m_particles; }
		std::vector<SpringJoint>& GetSpringJoints(void) { return m_springJoints; }
		std::vector<AnchoredSpring>& GetAnchoredSprings(void) { return m_anchoredSprings; }
		std::vector<StaticBox>& GetScenery(void) { return m_scenery; }

		void Step(float deltaTime);

	protected:

		void CheckLifetime(float deltaTime);
		void ResolveCollisions(void);
		void Integrate(Particle& particle, float deltaTime);

	private:
		const WorldConfiguration& m_worldConfiguration;
	
		core::PackedArray<Particle, 5000> m_particles;
		std::vector<core::ResourceID> m_particleHandles;

		std::vector<SpringJoint> m_springJoints;
		std::vector<AnchoredSpring> m_anchoredSprings;
		std::vector<WindForceGenerator> m_windForceGenerator;
		std::vector<StaticBox> m_scenery;

		GravityForceGenerator m_gravity;
	};
}
