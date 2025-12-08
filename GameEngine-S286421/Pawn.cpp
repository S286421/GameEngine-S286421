#include "Pawn.h"

int Pawn::GetX()
{
	return Position.x;
}

void Pawn::SetX(int x)
{
	Position.x = x;
}

int Pawn::GetY()
{
	return Position.y;
}

void Pawn::SetY(int y)
{
	Position.y = y;
}

void Pawn::UpdatePosition(int x, int y)
{
	DeltaMove.x += x;
	DeltaMove.y += y;
}

Pawn::Pawn(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent)
{
	Sprite = std::unique_ptr<Bitmap>(new Bitmap(renderer, path, x, y, isTransparent));
	this->Position.x = x;
	this->Position.y = y;
}

void Pawn::Draw()
{
	Sprite->Draw(Position.x, Position.y);
	this->DrawCollider(this->GetCollisionBounds());
}

void Pawn::Update()
{
}

SDL_Rect Pawn::GetCollisionBounds() const
{
	return Sprite->GetImageBounds();
}

void Pawn::DrawCollider(SDL_Rect Collider) const
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;
	SDL_GetRenderDrawColor(Sprite->GetRenderer().get(), &R, &G, &B, &A);

	SDL_SetRenderDrawColor(Sprite->GetRenderer().get(), 255, 255, 255, 255);

	const SDL_FRect dstRect = { static_cast<float>(Collider.x), static_cast<float>(Collider.y), static_cast<float>(Collider.w), static_cast<float>(Collider.h) };
	SDL_RenderRect(Sprite->GetRenderer().get(), &dstRect);
	SDL_SetRenderDrawColor(Sprite->GetRenderer().get(), R, G, B, A);
}

void Pawn::SetDeltaMove(int x, int y)
{
	DeltaMove.x = x;
	DeltaMove.y = y;
}

bool Pawn::IsOverlapping(const Pawn& Other, const SDL_Point& Delta)
{
	bool isColliding = false;

	SDL_Rect a = Sprite->GetImageBounds();
	SDL_Rect b = Other.Sprite->GetImageBounds();

	a.x += Delta.x;
	if (SDL_HasRectIntersection(&a, &b))
	{
		if (Delta.x > 0) a.x = b.x - a.w;
		else if (Delta.x < 0) a.x = b.x + b.w;
		isColliding = true;
	}

	a.y += Delta.y;
	if (SDL_HasRectIntersection(&a, &b))
	{
		if (Delta.y > 0) a.y = b.y - a.h;
		else if (Delta.y < 0) a.y = b.y + b.h;
		isColliding = true;
	}

	Position.x = a.x;
	Position.y = a.y;

	return isColliding;
}