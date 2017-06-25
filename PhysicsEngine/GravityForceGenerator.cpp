#include "GravityForceGenerator.h"
#include "Particle.h"

using namespace raven;

GravityForceGenerator::GravityForceGenerator(const WorldConfiguration& worldConfiguration) 
	: m_gravity(worldConfiguration.gravitation)
{}

void GravityForceGenerator::ApplyForceTo(Particle& particle)
{
	particle.acceleration = m_gravity;
}
