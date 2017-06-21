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

		void ToggleState(void);
		void UpdateForce(float deltaTime, Particle* particle);

	private:
		bool m_active;
		float m_windStrength;
		glm::vec2 m_position;
		glm::vec2 m_direction;
	};
}
