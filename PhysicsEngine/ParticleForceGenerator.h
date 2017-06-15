#pragma once

#include "Particle.h"

namespace raven
{
	class ParticleForceGenerator
	{
	public:
		virtual void UpdateForce(Particle& particle, float deltaTime) = 0;
		virtual ~ParticleForceGenerator() {};
	};
}