#pragma once
#include "Bitmap.h"
#include "Input.h"

class Pawn
{
protected:
	std::unique_ptr<Bitmap> Sprite;
private:
	int X;
	int Y;
public:
	Pawn(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent);

	int GetX();
	void SetX(int x);
	int GetY();
	void SetY(int y);
	void UpdatePosition(int x, int y);

	void Draw();

	virtual void Update();
};

