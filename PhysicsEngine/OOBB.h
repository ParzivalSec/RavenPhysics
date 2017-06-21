#pragma once

#include <vec2.hpp>

namespace raven
{
	namespace core
	{
		struct OOBB
		{
			glm::vec2 axis[2];
			glm::vec2 center;
			glm::vec2 w_h_halfExtend;
		};
	}
}
