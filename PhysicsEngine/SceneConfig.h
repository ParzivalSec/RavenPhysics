#pragma once

#include <stdint.h>

struct SceneConfig
{
	// Cloth Settings
	uint32_t columns;
	uint32_t rows;
	float clothNodeSize;

	// Primary ball count
	uint32_t ballCount;
};
