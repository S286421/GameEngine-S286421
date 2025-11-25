#pragma once
#include "Pawn.h"
class Player : public Pawn
{
public:
	Player(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent);

	void Update() override
	{
		Input::INSTANCE().Update();
		if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_UP))
			UpdatePosition(0, -1);
		if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_DOWN))
			UpdatePosition(0, 1);
		if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_LEFT))
			UpdatePosition(-1, 0);
		if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_RIGHT))
			UpdatePosition(1, 0);
	}
};

