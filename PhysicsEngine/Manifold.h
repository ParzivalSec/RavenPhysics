#pragma once

#include <vec2.hpp>
#include "Particle.h"

namespace raven
{
	struct Manifold
	{
		Manifold(Particle& a, Particle& b)
			: A(a)
			, B(b)
		{};

		Particle& A;
		Particle& B;
		glm::vec2 collisioNormal;
		float penetrationDepth;
	};
}
