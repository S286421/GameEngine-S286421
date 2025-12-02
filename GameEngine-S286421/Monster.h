#pragma once
#include "Pawn.h"
#include "Subscriber.h"
class Monster : public Pawn, public Subscriber
{
public:
	Monster(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent, Broker& broker);

	void Receive(const Message* message, const std::string& topic) override;
};

