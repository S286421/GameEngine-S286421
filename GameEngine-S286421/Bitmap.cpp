#include "Bitmap.h"
#include <vector>

/// <summary>
/// Initialises the bitmap; 'path' represents the file location of the texture, 'x' and 'y' represent the x and y positions for the bitmap
/// </summary>
/// <param name="renderer"></param>
/// <param name="path"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="isTransparent"></param>
Bitmap::Bitmap(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y,bool isTransparent)
{
	_renderer = renderer;
	_xPosition = x;
	_yPosition = y;

	float w, h;
	_texture = ResourceManager::INSTANCE().LoadTexture(path, isTransparent, _renderer);
	SDL_GetTextureSize(_texture.get(), &w, &h);
	_width = w;
	_height = h;
	this->path = path;
}

/// <summary>
/// Calls the Draw(int x, int y) function; used if no x or y positions are given
/// </summary>
void Bitmap::Draw()
{
	Draw(_xPosition, _yPosition);
}

/// <summary>
/// Renders the bitmap at the specified x and y positions
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Bitmap::Draw(int x, int y)
{
	_xPosition = x;
	_yPosition = y;

	SDL_FRect dstRect = { x, y, _width, _height };
	SDL_RenderTexture(_renderer.get(), _texture.get(), NULL, &dstRect);
}


/// <summary>
/// Renders the player with the next animation sprite in a vector of sprites every five frames
/// </summary>
/// <param name="moveSprites"></param>
/// <param name="Frame"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void Bitmap::DrawAnimation(const std::vector<SDL_Texture*> &moveSprites, int Frame, int x, int y)
{
	Frame /= 5;
	Frame %= moveSprites.size();
	//SDL_FRect dstRect = { _xPosition, _yPosition, _width, _height };
	SDL_FRect dstRect = {x, y, _width, _height};
	SDL_RenderTexture(_renderer.get(), moveSprites[Frame], NULL, &dstRect);

}

/// <summary>
/// Returns the bounds of the image as a SDL_Rect
/// </summary>
/// <returns></returns>
SDL_Rect Bitmap::GetImageBounds() const
{
	SDL_Rect a = { _xPosition, _yPosition, _width, _height };
	return a;
}

/// <summary>
/// Returns the shared_ptr of the renderer used by the bitmap
/// </summary>
/// <returns></returns>
std::shared_ptr<SDL_Renderer> Bitmap::GetRenderer()
{
	return _renderer;
}

/// <summary>
/// Returns the shared_ptr of the texture currently used by the bitmap
/// </summary>
/// <returns></returns>
std::shared_ptr<SDL_Texture> Bitmap::GetTextureRef()
{
	return _texture;
}