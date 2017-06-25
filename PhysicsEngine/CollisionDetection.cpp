#include "CollisionDetection.h"
#include "Particle.h"
#include "Manifold.h"
#include "ScenereyManifold.h"

#include <gtx/matrix_transform_2d.hpp>
#include <detail/func_geometric.hpp>
#include <ostream>
#include <iostream>

bool raven::coll::PointCircle(Manifold& m)
{
	Particle& A = m.A;
	Particle& B = m.B;

	float dist = glm::length(B.position - A.position);
	return dist - A.radius <= B.radius;
}

bool raven::coll::CircleCicle(Manifold& m)
{
	Particle& A = m.A;
	Particle& B = m.B;

	glm::vec2 n = B.position - A.position;
	float dist = glm::length(n);

	float rad = B.radius + A.radius;
	rad *= rad;

	if (dist * dist > rad)
	{
		return false;
	}

	if (dist != 0.0f)
	{
		m.penetrationDepth = rad - dist;
		// INFO: Recheck this in simulation
		m.collisioNormal = n / dist;
	}
	else
	{
		m.penetrationDepth = A.radius;
		m.collisioNormal = glm::vec2(0, 1);
	}
	
	return true;
}

bool raven::coll::CircleAABB(SceneryManifold& m)
{
	Particle& A = m.A;
	core::AABB& B = m.B.GetAABB();

	glm::vec2 centerDist = A.position - B.center;
	centerDist.x = glm::clamp(centerDist.x, -B.extend_w_h.x, B.extend_w_h.x);
	centerDist.y = glm::clamp(centerDist.y, -B.extend_w_h.y, B.extend_w_h.y);

	glm::vec2 closestPoint = B.center + centerDist;
	float dist = glm::length(closestPoint - A.position);

	if (dist > A.radius)
	{
		return false;
	}

	m.collisioNormal = glm::normalize(closestPoint - A.position);
	m.penetrationDepth = A.radius - dist;

	return true;
}

bool raven::coll::CircleOOBB(SceneryManifold& m)
{
	Particle& A = m.A;
	core::OOBB& B = m.B.GetOOBB();

	// Calculate inverseTransform of OOBB
	glm::mat3 oobbTrans(1.0f);
	oobbTrans = glm::rotate(oobbTrans, glm::radians(m.B.GetRotation()));
	oobbTrans = glm::translate(oobbTrans, B.center);

	// TODO: Remove me and move to oobb
	glm::mat3 invBoxMatrix = glm::inverse(oobbTrans);
	glm::vec2 transformedCircleCenter = invBoxMatrix * glm::vec3(A.position, 1.0f);
	glm::vec2 transformedBoxCenter = invBoxMatrix * glm::vec3(B.center, 1.0f);

	glm::vec2 centerDist = transformedCircleCenter - transformedBoxCenter;
	centerDist.x = glm::clamp(centerDist.x, -B.w_h_halfExtend.x, B.w_h_halfExtend.x);
	centerDist.y = glm::clamp(centerDist.y, -B.w_h_halfExtend.y, B.w_h_halfExtend.y);

	glm::vec2 closestPoint = transformedBoxCenter + centerDist;
	float dist = glm::length(closestPoint - transformedCircleCenter);

	if (dist > A.radius)
	{
		return false;
	}
	else if (dist == 0.0f)
	{
		// INFO: Somehow check how this is handles in real collision detection engines
		A.position += glm::normalize(-A.velocity) * 10.0f;
		return false;
	}

	m.collisioNormal = oobbTrans * glm::vec3(glm::normalize(closestPoint - transformedCircleCenter), 0.0f);
	m.penetrationDepth = A.radius - dist;

	return true;
}
