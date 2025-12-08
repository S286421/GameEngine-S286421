#pragma once
#include "Bitmap.h"
#include "Input.h"
#include <iostream>

class Pawn
{
protected:
	std::unique_ptr<Bitmap> Sprite;

public:
	Pawn(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent);

	int speed = 1;
	int gravity = 1;
	int maxFallSpeed = 10;
	bool Grounded = false;

	SDL_Point Position;
	SDL_Point DeltaMove;

	int GetX();
	void SetX(int x);
	int GetY();
	void SetY(int y);
	void UpdatePosition(int x, int y);

	void Draw();

	virtual void Update();

	SDL_Rect GetCollisionBounds() const;
	void DrawCollider(SDL_Rect Collider) const;

	void SetDeltaMove(int x, int y);
	bool IsOverlapping(const Pawn& Other, const SDL_Point& Delta);
};

