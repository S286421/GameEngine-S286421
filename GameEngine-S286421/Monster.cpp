#include "Monster.h"
#include <math.h>

Monster::Monster(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent, std::string pawnName) : Pawn(renderer, path, x, y, isTransparent, pawnName)
{
}

/// <summary>
/// Receives data using the Pawn::Receive function
/// </summary>
/// <param name="EventData"></param>
/// <param name="topic"></param>
void Monster::Receive(const IEventData* EventData, const std::string& topic)
{
	Pawn::Receive(EventData, topic);
	if (topic == "Test")
	{
		std::cout << "Received message: " << static_cast<const Message*>(EventData)->getMessage() << ", from topic: " << topic << std::endl;
	}
}

/// <summary>
/// Moves the enemy left and right continuously
/// </summary>
void Monster::Update()
{
	int i = sin(SDL_GetTicks() / 500) * 2;
	Position.x += i;
}
