#pragma once

#include <vec2.hpp>

namespace raven
{
	struct WorldConfiguration
	{
		glm::vec2 gravitation;
		uint32_t maxParticles;
	};
}