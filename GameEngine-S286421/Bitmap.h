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

	/// <summary>
	/// Returns the x position of the bitmap as an int
	/// </summary>
	/// <returns></returns>
	int GetX() const { return _xPosition; }

	/// <summary>
	/// Returns the y position of the bitmap as an int
	/// </summary>
	/// <returns></returns>
	int GetY() const { return _yPosition; }

	/// <summary>
	/// Returns the width of the bitmap as an int
	/// </summary>
	/// <returns></returns>
	int GetWidth() const { return _width; }

	/// <summary>
	/// Returns the height of the bitmap as an int
	/// </summary>
	/// <returns></returns>
	int GetHeight() const { return _height; }

	/// <summary>
	/// Sets the width of the bitmap to the given int
	/// </summary>
	/// <param name="width"></param>
	void SetWidth(int width) { _width = width; }

	/// <summary>
	/// Sets the height of the bitmap to the given width
	/// </summary>
	/// <param name="height"></param>
	void SetHeight(int height) { _height = height; }

	/// <summary>
	/// Returns the path of the texture used by the bitmap as a std::string
	/// </summary>
	/// <returns></returns>
	std::string GetPath() const { return path; }

	/// <summary>
	/// Sets the path of the texture used by the bitmap to the given path
	/// </summary>
	/// <param name="newPath"></param>
	void SetPath(const std::string& newPath) { path = newPath; }

	/// <summary>
	/// Returns whether the bitmap should have a transparent background as a boolean value
	/// </summary>
	/// <returns></returns>
	bool getIsTransparent() const { return _isTransparent; }

	/// <summary>
	/// Sets the _isTransparent variable to the given boolean value
	/// </summary>
	/// <param name="isTransparent"></param>
	void setIsTransparent(bool isTransparent) { _isTransparent = isTransparent; }

	/// <summary>
	/// Sets the _frameRate value to the given int
	/// </summary>
	/// <param name="frameRate"></param>
	void SetFrameRate(int frameRate) { _frameRate = frameRate; }

	/// <summary>
	/// Converts the given .bmp file to a SDL_Texture object with transparent background, and returns it
	/// </summary>
	/// <param name="bmp"></param>
	/// <param name="renderer"></param>
	/// <returns></returns>
	SDL_Texture* BMPtoTexture(const char* bmp, SDL_Renderer* renderer);

	/// <summary>
	/// Empty initialiser; only used for Bitmap::BMPtoTexture
	/// </summary>
	Bitmap();

private:
	std::shared_ptr<SDL_Renderer> _renderer;
	int _xPosition;
	int _yPosition;
	int _width;
	int _height;
	int _frameRate = 8;

	std::shared_ptr<SDL_Texture> _texture;
};

