#include "StaticBox.h"

#include <gtx/matrix_transform_2d.hpp>

using namespace raven;

StaticBox::StaticBox(const glm::vec2& position)
	: m_width(100)
	, m_height(100)
	, m_rotation(0)
	, m_center(position)
	, material(STEEL)
{
	CalculateBoundingCircle();
	CalculateAABB();
	CalculateOOBB();
}


StaticBox::StaticBox(const glm::vec2& position, float width, float height) 
	: m_width(width)
	, m_height(height)
	, m_rotation(0)
	, m_center(position)
	, material(STEEL)
{
	CalculateBoundingCircle();
	CalculateAABB();
	CalculateOOBB();
}


StaticBox::StaticBox(const glm::vec2& position, float width, float height, float rotation)
	: m_width(width)
	, m_height(height)
	, m_rotation(rotation)
	, m_center(position)
	, material(STEEL)
{
	CalculateBoundingCircle();
	CalculateAABB();
	CalculateOOBB();
}

void StaticBox::Rotate(float angle)
{
	m_rotation += angle;

	CalculateAABB();
	CalculateOOBB();
}

float StaticBox::GetRotation() const
{
	return m_rotation;
}


core::AABB& StaticBox::GetAABB()
{
	return m_aabb;
}


core::OOBB& StaticBox::GetOOBB()
{
	return m_oobb;
}


core::BoundingCircle& StaticBox::GetBoundingCircle()
{
	return m_boundingCircle;
}


void StaticBox::CalculateAABB()
{
	m_aabb.extend_w_h.x = m_width / 2.0f;
	m_aabb.extend_w_h.y = m_height / 2.0f;
	m_aabb.center = m_center;
}


void StaticBox::CalculateOOBB()
{
	glm::vec2 right = { 1, 0 };
	glm::vec2 up = { 0, 1 };

	m_oobb.w_h_halfExtend.x = m_width / 2.0f;
	m_oobb.w_h_halfExtend.y = m_height / 2.0f;
	m_oobb.center = m_center;

	glm::mat3 boxMatrix = glm::rotate(glm::mat3(1.0f), glm::radians(m_rotation));
	m_oobb.axis[0] = boxMatrix * glm::vec3(right, 1.0f);
	m_oobb.axis[1] = boxMatrix * glm::vec3(up, 1.0f);
}


void StaticBox::CalculateBoundingCircle()
{
	
}
