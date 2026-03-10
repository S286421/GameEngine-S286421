#include "RendererSystem.h"

/// <summary>
/// Creates an Entity Component System (ECS) with the given FileLocation, renderer, and transparency boolean, and adds it to the entity specified with the EntityID; returns the BitmapECS
/// </summary>
/// <param name="EntityID"></param>
/// <param name="ecs"></param>
/// <param name="FileLocation"></param>
/// <param name="renderer"></param>
/// <param name="isTransparent"></param>
/// <returns></returns>
BitmapECS RendererSystem::AddBitmapComponentToEntity(uint32_t EntityID, ECS& const ecs, std::string FileLocation, std::shared_ptr<SDL_Renderer> renderer, bool isTransparent)
{
	BitmapECS bitmap;
	bitmap.texture = ResourceManager::INSTANCE().LoadTexture(FileLocation, isTransparent, renderer);
	ecs.bitmaps[EntityID] = bitmap;
	ecs.entityIDs[EntityID] = ecs.entityIDs[EntityID] |= BitmapKey;
	return bitmap;
}

/// <summary>
/// Renders each entity using their given BitmapECS
/// </summary>
/// <param name="ecs"></param>
/// <param name="renderer"></param>
void RendererSystem::Render(ECS& const ecs, std::shared_ptr<SDL_Renderer> renderer)
{
	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++)
	{
		if (ecs.entityIDs[entityID] & (BitmapKey | PositionKey))
		{
			float width, height;
			SDL_GetTextureSize(ecs.bitmaps[entityID].texture.get(), &width, &height);
			SDL_FRect dstRect = { ecs.positions[entityID].X, ecs.positions[entityID].Y, width, height };

			SDL_RenderTexture(renderer.get(), ecs.bitmaps[entityID].texture.get(), NULL, &dstRect);
		}
	}
}
