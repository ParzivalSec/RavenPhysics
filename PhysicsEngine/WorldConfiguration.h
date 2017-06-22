#pragma once

#include <vec2.hpp>

namespace raven
{
	struct WorldConfiguration
	{
		/**
		 * Defines the strength of the gravity that is applied in this physic world
		 */
		glm::vec2 gravitation;
		/**
		 * Defines the maximum number of particles that can be processed (maybe has to me moved elsehwere due to max particles define by template)
		 */
		uint32_t maxParticles;
		/*
		 * Defines how often the collisions are resolved until considered in their final form
		 */
		uint32_t collisionIterations;
	};
}