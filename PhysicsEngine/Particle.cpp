#include "Particle.h"

using namespace raven;

Particle::Particle()
	: type(PARTICLE)
	, position({0, 0})
	, prevPosition(position)
	, acceleration({ 0, 0 })
	, forceAccumulator({ 0, 0 })
	, inverseMass(1.0f)
	, damping(0.4f)
	, lifeTime(1.0f)
	, restitution(2.0f)
	, radius(10.0f)
{}

Particle::Particle(glm::vec2 position)
	: type(PARTICLE)
	, position(position)
	, prevPosition(position)
	, acceleration({ 0, 0 })
	, forceAccumulator({ 0, 0 })
	, inverseMass(1.0f)
	, damping(0.4f)
	, lifeTime(1.0f)
	, restitution(2.0f)
	, radius(10.0f)
{}

Particle::Particle(glm::vec2 position, TYPE type) 
	: type(PARTICLE)
	, position(position)
	, prevPosition(position)
	, acceleration({ 0, 0 })
	, forceAccumulator({ 0, 0 })
	, inverseMass(1.0f)
	, damping(0.4f)
	, lifeTime(1.0f)
	, restitution(2.0f)
	, radius(10.0f)
{}

Particle::Particle(glm::vec2 position, glm::vec2 velocity, TYPE type)
	: type(PARTICLE)
	, position(position)
	, prevPosition(position)
	, velocity(velocity)
	, acceleration({ 0, 0 })
	, forceAccumulator({ 0, 0 })
	, inverseMass(1.0f)
	, damping(0.4)
	, lifeTime(1.0f)
	, restitution(2.0f)
	, radius(10.0f)
{}
