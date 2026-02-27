#pragma once
#include "Pawn.h"
#include "Subscriber.h"
class Monster : public Pawn
{
public:
	Monster(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent, std::string pawnName);

	void Receive(const IEventData* message, const std::string& topic) override;

	void Update() override;
};

