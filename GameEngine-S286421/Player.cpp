#include "Player.h"

Player::Player(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent, std::string pawnName) : Pawn(renderer, path, x, y, isTransparent, pawnName)
{
}

void Player::Update()
{
	DeltaMove.x = 0;
	DeltaMove.y = 0;

	Input::INSTANCE().UpdateKeyBoard();
	/*if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_UP))
		UpdatePosition(0, -speed);*/
	if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_DOWN) || Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_S))
		UpdatePosition(0, speed);
	if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_LEFT) || Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_A))
	{
		UpdatePosition(-speed, 0);
		isMovingLeft = true;
	}
	if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_RIGHT) || Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_D))
	{
		UpdatePosition(speed, 0);
		isMovingRight = true;
	}
	if (Input::INSTANCE().IsKeyUp(SDL_SCANCODE_RIGHT) || Input::INSTANCE().IsKeyUp(SDL_SCANCODE_D))
		isMovingRight = false;
	if (Input::INSTANCE().IsKeyUp(SDL_SCANCODE_LEFT) || Input::INSTANCE().IsKeyUp(SDL_SCANCODE_A))
		isMovingLeft = false;

	if (Input::INSTANCE().IsKeyDown(SDL_SCANCODE_Z))
		Broker::INSTANCE().Publish("Test", new Message(*this, "<Test message>"));

	if ((Input::INSTANCE().IsKeyDown(SDL_SCANCODE_SPACE) && Grounded) || (Input::INSTANCE().IsKeyDown(SDL_SCANCODE_W) && Grounded) || (Input::INSTANCE().IsKeyDown(SDL_SCANCODE_UP) && Grounded))
	{
		yVelocity = -25;
		Grounded = false;
	}

	if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_LSHIFT)) { speed = 4; }
	else { speed = 1; }

	if (Grounded) { yVelocity = 0; }

	yVelocity += gravity;
	DeltaMove.y += yVelocity;
	DeltaMove.y = std::min(DeltaMove.y, maxFallSpeed);
}