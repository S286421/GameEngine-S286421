#include "Pawn.h"

int Pawn::GetX()
{
	return X;
}

void Pawn::SetX(int x)
{
	X = x;
}

int Pawn::GetY()
{
	return Y;
}

void Pawn::SetY(int y)
{
	Y = y;
}

void Pawn::UpdatePosition(int x, int y)
{
	X += x;
	Y += y;
}

Pawn::Pawn(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent)
{
	Sprite = std::unique_ptr<Bitmap>(new Bitmap(renderer, path, x, y, isTransparent));
	this->X = x;
	this->Y = y;
}

void Pawn::Draw()
{
		Sprite.get()->Draw(X, Y);
}

void Pawn::Update()
{
}
