#include "Monster.h"

Monster::Monster(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent, Broker& broker) : Subscriber(broker), Pawn(renderer, path, x, y, isTransparent)
{
}

void Monster::Receive(const Message* message, const std::string& topic)
{
	std::cout << "Received message: " << message->getMessage() << ", from topic: " << topic << std::endl;
}
