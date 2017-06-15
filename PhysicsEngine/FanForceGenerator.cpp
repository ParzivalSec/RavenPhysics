#include "FanForceGenerator.h"

using namespace raven;

FanForceGenerator::FanForceGenerator(const glm::vec2 fanForceDirection, float fanStrength)
	: m_forceDirection(fanForceDirection)
	, m_forceStrength(fanStrength)
{}

void FanForceGenerator::UpdateForce(Particle& particle, float deltaTime)
{
	particle.ApplyForce(m_forceDirection * m_forceStrength);
}

FanForceGenerator::~FanForceGenerator()
{}
