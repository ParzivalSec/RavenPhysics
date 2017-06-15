#pragma once
#include <vector>

namespace raven
{
	class Particle;
	class ParticleForceGenerator;

	class ParticleForceRegistry
	{
	public:
		void Register(Particle* particle, ParticleForceGenerator* forceGenerator);
		void Unregister(Particle* particle, ParticleForceGenerator* forceGenerator);

		void Clear();

		void UpdateForces(float deltaTime);


	protected:
		struct ParticleRegistration
		{
			Particle* particle;
			ParticleForceGenerator* forceGenerator;
		};

		typedef std::vector<ParticleRegistration> Registry;
		Registry m_registrations;
	};
}
