#pragma once

#include <chrono>

namespace raven
{
	using namespace std::chrono;

	class Clock
	{
	public:
		void Start(void);
		const duration<float> GetElapsedTime(void) const;

		high_resolution_clock::time_point CurrentTime();

	private:
		high_resolution_clock::time_point m_startPoint;
	};
}
