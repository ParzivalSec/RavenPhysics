#pragma once

#include <vec2.hpp>

namespace raven
{
	namespace core
	{
		struct AABB
		{
			glm::vec2 center;
			glm::vec2 extend_w_h;
		};
	}
}
