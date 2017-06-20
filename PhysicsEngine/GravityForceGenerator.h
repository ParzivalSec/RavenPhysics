#pragma once

#include "vec2.hpp"
#include "WorldConfiguration.h"

namespace raven
{
	class Particle;

	class GravityForceGenerator
	{
	public:
		GravityForceGenerator(const WorldConfiguration& worldConfiguration);

		void ApplyForceTo(Particle& particle);

	private:
		glm::vec2 m_gravity;
	};
}
