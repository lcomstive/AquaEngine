#pragma once
#include <flecs.h>
#include <AquaEngine/API.hpp>

namespace AquaEngine
{
	struct AquaAPI Scene
	{
		flecs::world World;

		void Update(float deltaTime);
	};
}