#pragma once

#include <vec2.hpp>
#include "Material.h"

enum TYPE
{
	PARTICLE,
	BODY
};

enum SIMULATION_STATE
{
	ACTIVE,
	GROUNDED,
	INACTIVE
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

		SIMULATION_STATE state;
		TYPE type;
		glm::vec2 position;
		glm::vec2 prevPosition;
		glm::vec2 velocity;
		glm::vec2 acceleration;
		glm::vec2 forceAccumulator;
		float inverseMass;
		float damping;
		float lifeTime;
		float restitution;
		float radius;

		Material material;
	};
}
