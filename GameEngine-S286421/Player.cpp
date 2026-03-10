#include "Player.h"

/// <summary>
/// Initialises the player; assigns given parameters to private variables
/// </summary>
/// <param name="renderer"></param>
/// <param name="path"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="isTransparent"></param>
/// <param name="pawnName"></param>
/// <param name="rightMovement"></param>
/// <param name="leftMovement"></param>
/// <param name="rightOther"></param>
/// <param name="leftOther"></param>
Player::Player(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent, std::string pawnName, std::vector<SDL_Texture*> rightMovement, std::vector<SDL_Texture*> leftMovement, std::vector<SDL_Texture*> rightOther, std::vector<SDL_Texture*> leftOther) : Pawn(renderer, path, x, y, isTransparent, pawnName)
{
	_rightMovement = rightMovement;
	_leftMovement = leftMovement;
	_rightOther = rightOther;
	_leftOther = leftOther;
}

/// <summary>
/// Handles movement of the player during the game
/// </summary>
void Player::Update()
{
	FrameNumber++;

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

/// <summary>
/// Calls specific vectors for the Pawn::DrawAnimation() function depending on which direction the player character is moving and if the player character is in the air (calls the standard Pawn::Draw() function if the player character is not moving)
/// </summary>
void Player::Draw()
{
	if (isMovingRight && Grounded)
		DrawAnimation(_rightMovement, FrameNumber, GetX(), GetY());
	else if (isMovingLeft && Grounded)
		DrawAnimation(_leftMovement, FrameNumber, GetX(), GetY());
	else if (!Grounded && isMovingLeft)
		DrawAnimation(_leftOther, FrameNumber, GetX(), GetY());
	else if ((!Grounded && isMovingRight) || !Grounded)
		DrawAnimation(_rightOther, FrameNumber, GetX(), GetY());
	else
		Pawn::Draw();
}