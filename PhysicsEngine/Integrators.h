#pragma once

#include <vec3.hpp>

namespace raven
{
	namespace math
	{
		struct State
		{
			glm::vec3 position;
			glm::vec3 velocity;
			glm::vec3 acceleration;
			float inverseMass;
		};


		void EulerIntegrator(class Particle& particle);
	}
}