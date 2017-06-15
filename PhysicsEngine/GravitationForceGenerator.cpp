#include "GravitationForceGenerator.h"

#include "Particle.h"

using namespace raven;

GravitationForceGenerator::GravitationForceGenerator(const glm::vec2 gravity)
	: m_gravity(gravity)
{}

void GravitationForceGenerator::UpdateForce(Particle& particle, float deltaTime)
{
	particle.ApplyForce(m_gravity * particle.GetMass());
}

GravitationForceGenerator::~GravitationForceGenerator() {}
