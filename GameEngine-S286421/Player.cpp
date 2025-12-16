#include "Player.h"

Player::Player(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent) : Pawn(renderer, path, x, y, isTransparent)
{
}

void Player::Update()
{
	DeltaMove.x = 0;
	DeltaMove.y = 0;

	Input::INSTANCE().UpdateKeyBoard();
	/*if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_UP))
		UpdatePosition(0, -speed);*/
	if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_DOWN))
		UpdatePosition(0, speed);
	if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_LEFT))
		UpdatePosition(-speed, 0);
	if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_RIGHT))
		UpdatePosition(speed, 0);

	if (Input::INSTANCE().IsKeyDown(SDL_SCANCODE_P))
		Broker::INSTANCE().Publish("Test", new Message(*this, "<Test message>"));

	if (Input::INSTANCE().IsKeyDown(SDL_SCANCODE_SPACE) && Grounded)
	{
		DeltaMove.y = -15;
		Grounded = false;
	}

	DeltaMove.y += gravity;
	DeltaMove.y = std::min(DeltaMove.y, maxFallSpeed);
}