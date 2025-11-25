#include "SDL3/SDL.h"
#include "Bitmap.h"
#include "Player.h"
#include "Monster.h"
#include "Input.h"
#include "Debug.h"
#include "Background.h"
#include <iostream>
#include <random>

int main(int argc, char* argv[])
{
	if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		printf("error initializing SDL: %s\n", SDL_GetError());

	SDL_Window* win = SDL_CreateWindow("GAME", 1000, 1000, 0);
	SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	std::shared_ptr<SDL_Renderer> rendere = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(win, NULL), sdl_deleter());
	Background background;
	SDL_Texture* texture = background.LoadBackground(rendere, "./../Assets/backgroundtest.bmp");

	Player player(rendere, "./../Assets/monster.bmp", 100, 200, false);
	Monster monster(rendere, "./../Assets/monstertrans.bmp", 200, 200, true);

	//VerboseDebugPrintF(Verbosity::Info, "UOSGameEngine started with %d arguments\n", argc);

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

		SDL_RenderClear(rendere.get());
		background.RenderBackground(rendere, texture);
		player.Draw();
		monster.Draw();
		SDL_RenderPresent(rendere.get());
		Input::INSTANCE().LateUpdate();
		SDL_Delay(16);
	}

	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

