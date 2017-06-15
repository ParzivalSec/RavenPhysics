#pragma once

#include <vec2.hpp>

namespace raven
{
	class Particle
	{
	public:
		Particle(glm::vec2 initialPosition, glm::vec2 initialVelocity);

		void SetMass(float mass) { m_inverseMass = 1.0f / mass; }
		void SetInverseMass(float inverseMass) { m_inverseMass = inverseMass; }
		void SetAcceleration(const glm::vec2 acceleration) { m_acceleration = acceleration; }
		void SetDamping(float damping) { m_damping = damping; }

		const glm::vec2& GetPosition(void) const { return m_position; }
		const glm::vec2& GetVelocity(void) const { return m_velocity; }
		const glm::vec2& GetAcceleration(void) const { return m_acceleration; }
		float GetDamping(void) const { return m_damping; }
		float GetInverseMass(void) const { return m_inverseMass; }
		float GetMass(void) const { return 1.0f / m_inverseMass; }

		void ApplyForce(const glm::vec2& force);
		void Integrate(float deltaTime /*void (*Integrator)(Particle&) --> add this later! */);

	protected:

		void ClearAccumulator(void);

		glm::vec2 m_position;
		glm::vec2 m_velocity;
		glm::vec2 m_acceleration;

		/**
		 * Holds an accumulated force that is 
		 * only valid for one physic step
		 */
		glm::vec2 m_forceAccum;

		/*
		 * Hold the amount of damping applied to linear motion
		 * Only a rough approximation ti remove enery added through
		 * numerical instability in the integrator
		 */
		float m_damping;

		/**
		 * Stores the inverse mass of the particle. This is useful
		 * to get objects with infinite mass (unmoveable)
		 * (unstable in numerical simulation)
		 */
		float m_inverseMass;
	};
}