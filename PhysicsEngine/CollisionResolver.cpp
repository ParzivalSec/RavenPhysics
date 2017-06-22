#include "CollisionResolver.h"
#include "Manifold.h"
#include "ScenereyManifold.h"
#include <detail/func_geometric.inl>

using namespace raven;

void coll::ResolveCollision(Manifold& m)
{
	glm::vec2 relVel = m.B.velocity - m.A.velocity;

	float relVelNormal = glm::dot(relVel, m.collisioNormal);

	// Velocities are seprarting
	if (relVelNormal > 0)
	{
		return;
	}

	float minRes = glm::min(m.A.restitution, m.B.restitution);

	// Calculate impulse strength
	float impStr = -(1 + minRes) * relVelNormal;
	impStr /= m.A.inverseMass + m.B.inverseMass;

	glm::vec2 impulse = impStr * m.collisioNormal;
	m.A.velocity -= m.A.inverseMass * impulse;
	m.B.velocity += m.B.inverseMass * impulse;
}

void coll::ResolveStaticCollision(SceneryManifold& m)
{
	float normStr = m.collisioNormal.x * m.A.velocity.x + m.collisioNormal.y * m.A.velocity.y;
	glm::vec2 velNormal = m.collisioNormal * normStr;
	m.A.velocity -= 2.0f * velNormal;
}
