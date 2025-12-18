#include "SDL3/SDL.h"
#include "Bitmap.h"
#include "Player.h"
#include "Monster.h"
#include "Input.h"
#include "Debug.h"
#include "GameObject.h"
#include "BitmapComponent.h"
#include "ECS.h"
#include "RendererSystem.h"
#include "MovementSystem.h"
#include "StackArenaAllocator.h"
#include "Sol/sol.hpp"
#include "ScriptComponent.h"
#include "imgui.h"
#include "ImGui/backends/imgui_impl_sdl3.h"
#include "ImGui/backends/imgui_impl_sdlrenderer3.h"
#include "EditorGui.h"
#include "AssetWindow.h"
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

	Hierarchy::INSTANCE().Init(rendere);

	Player player(rendere, "./../Assets/monstertrans.bmp", 100, 200, true);
	Pawn platform(rendere, "./../Assets/platform-test.bmp", 100, 600, true);
	Monster enemy(rendere, "./../Assets/monstertrans.bmp", 400, 486, true);

	enemy.Subscribe("MouseButtonUpdate");
	enemy.Subscribe("MousePositionUpdate");
	enemy.Subscribe("MouseWheelUpdate");
	player.Subscribe("MouseButtonUpdate");
	player.Subscribe("MousePositionUpdate");
	player.Subscribe("MouseWheelUpdate");

	SDL_Surface* background = SDL_LoadBMP("./../Assets/nicerbackground.bmp");
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(rendere.get(), background);

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

	//ImGui//

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
	style.ScaleAllSizes(main_scale);
	style.FontScaleDpi = main_scale;

	ImGui_ImplSDL3_InitForSDLRenderer(win, rendere.get());
	ImGui_ImplSDLRenderer3_Init(rendere.get());

	//ImGui//

	std::vector<Pawn*> Colliders;
	Colliders.push_back(&platform);
	Colliders.push_back(&enemy);

	AssetWindow window(rendere);

	bool IsRunning = true;

	while (IsRunning)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			Input::INSTANCE().UpdateMouse(e);
			ImGui_ImplSDL3_ProcessEvent(&e);
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
		
		Input::INSTANCE().UpdateKeyBoard();

		player.Update();

		int oldY = player.Position.y;


		if (player.IsOverlapping(Colliders, player.DeltaMove))
		{
			auto it = std::find(player.currentCollisions.begin(), player.currentCollisions.end(), &enemy);
			if (it != player.currentCollisions.end())
			{
				IsRunning = false;
			}

		}


		if (player.Position.y == oldY + player.DeltaMove.y && player.DeltaMove.y > 0)
			player.Grounded = false;
		else if (player.DeltaMove.y >= 0)
			player.Grounded = { player.Position.y < oldY + player.DeltaMove.y };

		SDL_RenderClear(rendere.get());

		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
		EditorGui::INSTANCE().DrawWindows();
		window.DrawWindow();
		ImGui::ShowDemoWindow();
		ImGui::Begin("Sir Windowsworth the First");
		if (ImGui::Button("Press me"))
			std::cout << "Button Pressed" << std::endl;
		ImGui::End();

		/*RootTransform.UpdateTransform(Transform{});
		gameObject.Update();
		gameObject2.Update();
		monster.Subscribe("Test");*/

		SDL_RenderTexture(rendere.get(), backgroundTexture, NULL, NULL);
		Hierarchy::INSTANCE().DrawHierarchyItems();
		player.Draw();
		platform.Draw();
		enemy.Draw();
		//RendererSystem::Render(ecs, rendere);
		MovementSystem::UpdatePositions(ecs);

		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		ImGui::Render();
		SDL_SetRenderScale(rendere.get(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		SDL_SetRenderDrawColorFloat(rendere.get(), clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), rendere.get());

		SDL_RenderPresent(rendere.get());

		Input::INSTANCE().LateUpdate();

		SDL_Delay(16);
	}

	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

