#pragma once

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL_Deleter.h"
#include "ResourceManager.h"
#include <memory>
#include <string>
#include <vector>

class Bitmap
{
public:
	Bitmap(
		std::shared_ptr<SDL_Renderer> renderer,
		const std::string path, int x, int y, bool isTransparent);
	void Draw();
	void Draw(int x, int y);
	void DrawAnimation(const std::vector< SDL_Texture*> &moveSprites, int Frame, int x, int y);
	SDL_Rect GetImageBounds() const;
	std::shared_ptr<SDL_Renderer> GetRenderer();
	std::shared_ptr<SDL_Texture> GetTextureRef();

	bool _isTransparent;
	std::string path;

	int GetX() const { return _xPosition; }
	int GetY() const { return _yPosition; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
	void SetWidth(int width) { _width = width; }
	void SetHeight(int height) { _height = height; }
	std::string GetPath() const { return path; }
	void SetPath(const std::string& newPath) { path = newPath; }
	bool getIsTransparent() const { return _isTransparent; }
	void setIsTransparent(bool isTransparent) { _isTransparent = isTransparent; }
	void SetFrameRate(int frameRate) { _frameRate = frameRate; }

private:
	std::shared_ptr<SDL_Renderer> _renderer;
	int _xPosition;
	int _yPosition;
	int _width;
	int _height;
	int _frameRate = 8;

	std::shared_ptr<SDL_Texture> _texture;
};

