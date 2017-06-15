#include "ParticleForceRegistry.h"

#include <algorithm>
#include "Particle.h"
#include "ParticleForceGenerator.h"

using namespace raven;

void ParticleForceRegistry::Register(Particle* particle, ParticleForceGenerator* forceGenerator)
{
	m_registrations.push_back({ particle, forceGenerator });
}

void ParticleForceRegistry::Unregister(Particle* particle, ParticleForceGenerator* forceGenerator)
{
	m_registrations.erase(std::remove_if(m_registrations.begin(), m_registrations.end(), [&particle, &forceGenerator](const ParticleRegistration& reg)
	{
		if (&reg.particle == &particle && reg.forceGenerator == forceGenerator)
		{
			return true;
		}
		else
		{
			return false;
		}

	}), m_registrations.end());
}

void ParticleForceRegistry::Clear()
{
	m_registrations.clear();
}

void ParticleForceRegistry::UpdateForces(float deltaTime)
{
	for (size_t reg = 0; reg < m_registrations.size(); reg++)
	{
		Particle* particle = m_registrations[reg].particle;
		m_registrations[reg].forceGenerator->UpdateForce(*particle, deltaTime);
	}
}
