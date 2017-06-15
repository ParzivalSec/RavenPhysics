#pragma once

#include "ParticleForceGenerator.h"

namespace raven
{
	class FanForceGenerator : public ParticleForceGenerator
	{
	public:
		FanForceGenerator(const glm::vec2 fanForceDirection, float fanStrength);

		virtual void UpdateForce(Particle& particle, float deltaTime) override;

		void SetStrength(float strength) { m_forceStrength = strength; }

		~FanForceGenerator() override;

	protected:
		glm::vec2 m_forceDirection;
		float m_forceStrength;
	};
}

