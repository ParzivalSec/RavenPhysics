#pragma once
#include "OOBB.h"
#include "AABB.h"
#include "BoudingCircle.h"
#include "Material.h"

namespace raven
{
	class StaticBox
	{
	public:
		StaticBox(const glm::vec2& position);
		StaticBox(const glm::vec2& position, float width, float height);
		StaticBox(const glm::vec2& position, float width, float height, float rotation);

		void Rotate(float angle);
		float GetRotation(void) const;

		core::AABB& GetAABB(void);
		core::OOBB& GetOOBB(void);
		core::BoundingCircle& GetBoundingCircle(void);

		Material material;

	protected:
		void CalculateAABB();
		void CalculateOOBB();
		void CalculateBoundingCircle();

	private:

		float m_width;
		float m_height;
		float m_rotation;
		glm::vec2 m_center;

		// Bounding volumes for boxes
		core::BoundingCircle m_boundingCircle;
		core::AABB m_aabb;
		core::OOBB m_oobb;
	};
}
