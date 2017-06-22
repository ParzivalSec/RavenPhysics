#pragma once

namespace raven
{
	struct Manifold;
	struct SceneryManifold;

	namespace coll
	{
		bool PointCircle(Manifold& m);
		bool CircleCicle(Manifold& m);

		bool CircleAABB(SceneryManifold& m);
		bool CircleOOBB(SceneryManifold& m);
	}
}
