#pragma once

#include "PackedArray.h"
#include <vec2.hpp>

namespace raven
{
	class World;

	class AnchoredSpring
	{
	public:
		AnchoredSpring(float springConstant, float restLength);
		AnchoredSpring(const glm::vec2& anchor, core::ResourceID particle, float springConstant, float restLength);

		void AddParticle(core::ResourceID particle);
		void SetAnchor(const glm::vec2 anchor);

		void UpdateForce(float deltaTime, World& world);

	private:
		core::ResourceID m_particle;
		glm::vec2 m_anchor;
		float m_springConstant;
		float m_restLength;
	};
}
