#include "SDL3/SDL.h"
#include "Bitmap.h"
#include "Player.h"
#include "Monster.h"
#include "Input.h"
#include "Debug.h"
#include "Background.h"
#include "GameObject.h"
#include "BitmapComponent.h"
#include "ECS.h"
#include "RendererSystem.h"
#include "MovementSystem.h"
#include "StackArenaAllocator.h"
#include "Sol/sol.hpp"
#include "ScriptComponent.h"
#include <iostream>
#include <random>

int main(int argc, char* argv[])

{
	StackArenaAllocator stack(1024);

	std::pmr::vector<int> numbers(&stack);
	for (int i = 0; i < 10; ++i)
		numbers.push_back(i * 10);

	std::cout << "Numbers : ";
	for (int n : numbers) std::cout << n << " ";
	std::cout << "\n";

	std::pmr::string msg("Hello from StackArena!", &stack);
	std::cout << msg << "\n";

	std::cout << "Resetting stack...\n";
	stack.reset();

	if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		printf("error initializing SDL: %s\n", SDL_GetError());

	SDL_Window* win = SDL_CreateWindow("GAME", 1000, 1000, 0);
	SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	std::shared_ptr<SDL_Renderer> rendere = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(win,NULL), sdl_deleter());
	Background background;
	SDL_Texture* texture = background.LoadBackground(rendere, "./../Assets/backgroundtest.bmp");

	Broker broker;
	Player player(rendere, "./../Assets/monstertrans.bmp", 100, 200, true, broker);

	Monster monster(rendere, "./../Assets/monstertrans.bmp", 200, 200, true, broker);

	//VerboseDebugPrintF(Verbosity::Info, "UOSGameEngine started with %d arguments\n", argc);
	Transform RootTransform;

	GameObject gameObject;
	std::shared_ptr<BitmapComponent> temp = std::make_shared<BitmapComponent>(rendere, "./../Assets/monster.bmp", 300, 200, false, &gameObject);
	gameObject.AddComponent(temp);
	gameObject.transform.Location.x = 500;
	gameObject.transform.Location.y = 200;

	RootTransform.AddChild(&gameObject.transform);

	GameObject gameObject2;
	std::shared_ptr<BitmapComponent> temp2 = std::make_shared<BitmapComponent>(rendere, "./../Assets/monstertrans.bmp", 300, 200, false, &gameObject2);
	gameObject2.AddComponent(temp2);
	gameObject2.transform.Location.x = 10;
	gameObject2.transform.Location.y = 20;

	gameObject.transform.AddChild(&gameObject2.transform);

	ECS ecs;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

	for(int i = 0; i < MAX_ENTITIES; i++)
	{
		RendererSystem::AddBitmapComponentToEntity(i, ecs, "./../Assets/kaboom.png", rendere,false);
		MovementSystem::AddPositionComponentToEntity(i, ecs, 400, 400);
		float RandomX = dist(gen);
		float RandomY = dist(gen);
		float RandomGrav = dist(gen);
		MovementSystem::AddVelocityComponentToEntity(i, ecs, 10*RandomX, RandomY, RandomGrav);
	}
	
	/*std::shared_ptr<ScriptComponent> scriptTest = std::make_shared<ScriptComponent>("./../luaSrc/ComponentTest.lua", &gameObject);
	gameObject.AddComponent(scriptTest);*/

	bool IsRunning = true;

	while (IsRunning)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type) {
			case SDL_EVENT_KEY_DOWN:
				switch (e.key.key) {
				case SDLK_ESCAPE:
					IsRunning = false;
				default:
					break;
				}
				break;

			case SDL_EVENT_QUIT:
			IsRunning = false;
				break;
			default:
				break;
			}
		}
		
		player.Update();

		int oldY = player.Position.y;

		player.IsOverlapping(monster, player.DeltaMove);

		if (player.IsOverlapping(monster, player.DeltaMove))
		{
			std::cout << "Colliding!" << std::endl;
		}

		if (player.Position.y == oldY + player.DeltaMove.y && player.DeltaMove.y > 0)
			player.Grounded = false;
		else if (player.DeltaMove.y >= 0)
			player.Grounded = { player.Position.y < oldY + player.DeltaMove.y };

		SDL_RenderClear(rendere.get());

		background.RenderBackground(rendere, texture);

		/*RootTransform.UpdateTransform(Transform{});
		gameObject.Update();
		gameObject2.Update();
		monster.Subscribe("Test");*/

		player.Draw();
		//monster.Draw();
		RendererSystem::Render(ecs, rendere);
		MovementSystem::UpdatePositions(ecs);
		SDL_RenderPresent(rendere.get());

		Input::INSTANCE().LateUpdate();

		SDL_Delay(16);
	}

	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

