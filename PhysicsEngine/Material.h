#pragma once

namespace raven
{
	enum Material  
	{
		STEEL = 0,
		STEEL_LUBRICATED = 1,
		ALUMINIUM = 2,
		RUBBER = 3,
		CONCRETE = 4,
		SNOW = 5,
	};

	static float StaticFrictionLUT[][5] = 
	{
		// Steel
		{0.7f, 0.12f, 0.61f, 0.8f, 0.9f },
		// Lubricated Steel
		{ 0.12f, 0.1f, 0.04f, 0.22f, 0.32f },
		// Aluminium
		{ 0.61f, 0.04f, 0.2f, 0.4f, 0.6f },
		// Rubber
		{ 0.8f, 0.22f, 0.4f, 1.2f, 1.0f },
		// Concrete
		{ 0.9f, 0.32f, 0.6f, 1.0f, 1.5f }
	};

	static float KineticFrictionLUT[][5] =
	{
		// Steel
		{ 0.57f, 0.07f, 0.47f, 0.8f, 0.9f },
		// Lubricated Steel
		{ 0.07f, 0.01f, 0.06f, 0.22f, 0.32f },
		// Aluminium
		{ 0.47f, 0.06f, 0.1f, 0.4f, 0.6f },
		// Rubber
		{ 0.75f, 0.15f, 0.4f, 1.1f, 0.8f },
		// Concrete
		{ 0.9f, 0.32f, 0.6f, 0.8f, 1.5f }
	};

	static float MassLUT[] =
	{
		4.0f,
		4.0f, 
		1.5f,
		1.2f,
		6.0f
	};
}