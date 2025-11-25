#include "Background.h"

SDL_Texture* Background::LoadBackground(std::shared_ptr<SDL_Renderer> renderer, const char *FileLocation)
{
	SDL_Surface* background = SDL_LoadBMP(FileLocation);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.get(), background);
	return texture;
}

void Background::RenderBackground(std::shared_ptr<SDL_Renderer> renderer, SDL_Texture* texture)
{
	SDL_RenderTexture(renderer.get(), texture, NULL, NULL);
}
