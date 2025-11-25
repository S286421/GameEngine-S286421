#pragma once
#include "Pawn.h"
class Monster : public Pawn
{
public:
	Monster(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent);
};

