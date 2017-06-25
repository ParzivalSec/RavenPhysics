#pragma once

#include <vec2.hpp>

namespace raven
{
	class Particle;

	class WindForceGenerator
	{
	public:
		WindForceGenerator(const glm::vec2 position, const glm::vec2& direction, float strength);

		const glm::vec2& GetPosition(void) const;
		const glm::vec2& GetDirection(void) const;

		void SetStrength(float strength);
		void SetBounds(const glm::vec2& bounds);
		void SetDistance(float distance);

		void ToggleState(void);
		void UpdateForce(float deltaTime, Particle* particle);
	
		glm::vec2 m_lower_upperBounds;

	private:
		bool m_active;
		float m_windStrength;
		float m_maxDistance;
		glm::vec2 m_position;
		glm::vec2 m_direction;
	};
}
