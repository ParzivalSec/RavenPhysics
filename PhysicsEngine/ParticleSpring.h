#pragma once
#include "ParticleForceGenerator.h"

namespace raven 
{
	class Particle;

	class ParticleSpring : public ParticleForceGenerator
	{
	public:
		ParticleSpring(Particle* other, float springConstant, float restLength);

		void UpdateForce(Particle& particle, float deltaTime) override;
		~ParticleSpring() override;

	protected:
		Particle* m_other;

		float m_springConstant;
		float m_restLength;

	};
}
