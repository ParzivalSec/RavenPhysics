#pragma once

#include "PackedArray.h"

namespace raven
{
	class World;

	class SpringJoint
	{
	public:
		SpringJoint(float springConstant, float restLength);
		SpringJoint(core::ResourceID particle, core::ResourceID other, float springConstant, float restLength);

		void AddParticle(core::ResourceID particle);

		core::ResourceID GetParticle(uint32_t index) { return m_particles[index]; }

		void UpdateForce(float deltaTime, World& world);

	private:
		core::ResourceID m_particles[2];
		float m_springConstant;
		float m_restLength;
	};
}
