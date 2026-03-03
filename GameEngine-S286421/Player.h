#pragma once
#include "Pawn.h"
#include "Publisher.h"
#include "Message.h"
class Player : public Pawn
{
public:
	Player(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent, std::string pawnName);

	void Update() override;

	bool isMovingRight = false;
	bool isMovingLeft = false;

	bool canDoubleJump = true;
};

