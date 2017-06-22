#pragma once

namespace raven
{
	struct Manifold;
	struct SceneryManifold;

	namespace coll
	{
		void ResolveCollision(Manifold& m);
		void ResolveStaticCollision(SceneryManifold& m);
	}
}
