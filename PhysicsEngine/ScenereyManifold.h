#pragma once

#include <vec2.hpp>
#include "Particle.h"
#include "StaticBox.h"

namespace raven
{
	struct SceneryManifold
	{
		SceneryManifold(Particle& a, StaticBox& b)
			: A(a)
			, B(b)
		{}

		Particle& A;
		StaticBox& B;
		glm::vec2 collisioNormal;
		float penetrationDepth;
	};
}
