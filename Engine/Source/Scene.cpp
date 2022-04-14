#include <AquaEngine/Scene.hpp>

using namespace AquaEngine;

void Scene::Update(float deltaTime)
{
	World.progress(deltaTime);
}