#include "RendererSystem.h"

BitmapECS RendererSystem::AddBitmapComponentToEntity(uint32_t EntityID, ECS& const ecs, std::string FileLocation, std::shared_ptr<SDL_Renderer> renderer, bool isTransparent)
{
	BitmapECS bitmap;
	bitmap.texture = ResourceManager::INSTANCE().LoadTexture(FileLocation, isTransparent, renderer);
	ecs.bitmaps[EntityID] = bitmap;
	ecs.entityIDs[EntityID] = ecs.entityIDs[EntityID] |= BitmapKey;
	return bitmap;
}

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
