#pragma once
#include "ParticleForceGenerator.h"

namespace raven
{
	class GravitationForceGenerator : public ParticleForceGenerator
	{
	public:
		GravitationForceGenerator(const glm::vec2 gravity);

		void UpdateForce(Particle& particle, float deltaTime) override;
		~GravitationForceGenerator() override;

	protected:
		glm::vec2 m_gravity;
	};
}

