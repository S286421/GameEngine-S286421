#pragma once
#include "Pawn.h"
#include "Publisher.h"
#include "Message.h"
class Player : public Pawn
{
public:
	Player(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent, std::string pawnName, std::vector<SDL_Texture*> rightMovement, std::vector<SDL_Texture*> leftMovement, std::vector<SDL_Texture*> rightOther, std::vector<SDL_Texture*> leftOther);

	void Update() override;
	void Draw() override;

	bool isMovingRight = false;
	bool isMovingLeft = false;

private:
	std::vector<SDL_Texture*> _rightMovement;
	std::vector<SDL_Texture*> _leftMovement;
	std::vector<SDL_Texture*> _rightOther;
	std::vector<SDL_Texture*> _leftOther;
	int FrameNumber = 0;
};

