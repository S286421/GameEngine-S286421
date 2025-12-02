#include "Player.h"

Player::Player(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent, Broker &broker) : Pawn(renderer, path, x, y, isTransparent), Publisher(broker)
{
}

void Player::Update()
{
	Input::INSTANCE().Update();
	if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_UP))
		UpdatePosition(0, -5);
	if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_DOWN))
		UpdatePosition(0, 5);
	if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_LEFT))
		UpdatePosition(-5, 0);
	if (Input::INSTANCE().IsKeyHeld(SDL_SCANCODE_RIGHT))
		UpdatePosition(5, 0);

	if (Input::INSTANCE().IsKeyDown(SDL_SCANCODE_P))
		Publish("Test", new Message("<Test message>"));
}