#include "CollisionResolver.h"
#include "Manifold.h"
#include "ScenereyManifold.h"
#include <detail/func_geometric.inl>
#include <SFML/Graphics/Glsl.hpp>
#include <detail/func_trigonometric.hpp>

using namespace raven;

void coll::ResolveCollision(Manifold& m)
{
	glm::vec2 relVel = m.B.velocity - m.A.velocity;

	float relVelNormal = glm::dot(relVel, m.collisioNormal);

	// Velocities are seprarting
	if (relVelNormal >= 0)
	{
		return;
	}

	float minRes = glm::min(m.A.restitution, m.B.restitution);

	// Calculate impulse strength
	float impStr = -(1.0f + minRes) * relVelNormal;
	impStr /= m.A.inverseMass + m.B.inverseMass;

	glm::vec2 impulse = impStr * m.collisioNormal;

	m.A.velocity -= m.A.inverseMass * impulse;
	m.B.velocity += m.B.inverseMass * impulse;
}

void coll::ResolveStaticCollision(SceneryManifold& m)
{
	float normStr = m.collisioNormal.x * m.A.velocity.x + m.collisioNormal.y * m.A.velocity.y;

	if (glm::length(m.A.velocity) < 10.0f)
	{
		const float k_slop = 0.01f; // Penetration allowance
		const float percent = 0.2f; // Penetration percentage to correct
		glm::vec2 correction = (std::max( m.penetrationDepth - k_slop, 0.0f ) / (m.A.inverseMass)) * percent * m.collisioNormal;
		m.A.position -= m.A.inverseMass * correction;

		// Calculate friction
		float fMax = glm::length(StaticFrictionLUT[m.A.material][m.B.material] * MassLUT[m.A.material] * m.A.acceleration * glm::cos(glm::radians(m.B.GetRotation())));
		float fStat = glm::length(MassLUT[m.A.material] * m.A.acceleration * glm::sin(glm::radians(m.B.GetRotation())));

		if (fStat > fMax)
		{
			// Apply kinematic friction to body
			glm::vec2 fKin = KineticFrictionLUT[m.A.material][m.B.material] * MassLUT[m.A.material] * m.A.acceleration * glm::cos(glm::radians(m.B.GetRotation()));
			glm::vec2 velocity = MassLUT[m.A.material] * m.A.acceleration * glm::sin(glm::radians(m.B.GetRotation())) * glm::length(m.A.velocity);
			velocity -= fKin;

			m.A.velocity = velocity;
			return;
		}

		m.A.velocity *= 1.0f;
		return;
	}

	glm::vec2 velNormal = m.collisioNormal * normStr;
	m.A.velocity -= 1.95f * velNormal;
}
