#pragma once

#include <vec2.hpp>

enum TYPE
{
	PARTICLE,
	BODY
};

namespace raven
{
	class Particle
	{
	public:
		Particle();
		Particle(glm::vec2 position);
		Particle(glm::vec2 position, TYPE type);
		Particle(glm::vec2 position, glm::vec2 velocity, TYPE type);

		void SetMass(float newMass) { inverseMass = 1.0f / newMass; }

		TYPE type;
		glm::vec2 position;
		glm::vec2 prevPosition;
		glm::vec2 velocity;
		glm::vec2 acceleration;
		glm::vec2 forceAccumulator;
		float inverseMass;
		float damping;

	};
}
