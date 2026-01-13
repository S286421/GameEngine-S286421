#include "include.h"

void SavePlayerToJson(Pawn& player)
{
	nlohmann::json SaveData;
	SaveData["Player"] = { {"X",player.GetX()}, {"Y",player.GetY()} };
	
	std::ofstream file("savegame.json");
	file << SaveData.dump(4);
	file.close();

	std::cout << "Saved to savegame.json\n";
}

int LoadPlayerFromJson(Pawn& player)
{
	std::ifstream file("savegame.json");
	if (!file.is_open())
	{
		std::cerr << "Could not open savegame.json\n";
		return 1;
	}

	nlohmann::json LoadData;
	file >> LoadData;
	file.close();

	if (LoadData.contains("Player"))
	{
		player.SetX(LoadData["Player"]["X"].get<int>());
		player.SetY(LoadData["Player"]["Y"].get<int>());
		std::cout << "Loaded from savegame.json\n";
		return 0;
	}
	else
	{
		std::cerr << "Invalid save data\n";
		return 1;
	}
}

void DrawProfileData(ImGuiIO& io)
{
	ImGui::Begin("Profiler");

	static int selectedFrame = -1;
	static FrameMap* Snapshot;
	static std::vector<float>* FrameTimes;

	if (ImGui::Button("take snapshot"))
	{
		Snapshot = &(ProfilerSystem::Instance().GetFrameData());
		FrameTimes = &(ProfilerSystem::Instance().GetFrameTimes());
	}

	ImGui::SameLine();
	static bool LiveFlameGraph = true;
	ImGui::Checkbox("Live Flame Graph", &LiveFlameGraph);
	if (LiveFlameGraph) { selectedFrame = -1; }

	static int range[2] = { 0, 100 };
	if (FrameTimes && FrameTimes->size() > 100)
	{
		ImGui::SliderInt2("Frame Range", range, 0, FrameTimes->size());
		if (range[0] >= range[1]) { range[0] = range[1] - 1; }
		std::vector<float> subData(FrameTimes->cbegin() + range[0], FrameTimes->cbegin() + range[1]);

		int tempHistSelection = ImGui::MyPlotHistogram("Frame data", subData.data(), subData.size());
		if (tempHistSelection != -1)
		{
			LiveFlameGraph = false;
			selectedFrame = tempHistSelection;
		}
	}

	FrameMap& previousFrame = ProfilerSystem::Instance().GetLastFrameData();
	if (!LiveFlameGraph && selectedFrame != -1)
	{
		previousFrame.clear();
		for (auto const [SampleName, samples] : *Snapshot) { previousFrame[SampleName].push_back(samples[range[0] + selectedFrame]); }
	}
	else { LiveFlameGraph = false; }

	ImGui::LabelText("Frame Data Count", std::to_string(previousFrame.size()).c_str());

	ImDrawList* drawlist = ImGui::GetCurrentWindow()->DrawList;
	ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
	ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
	if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
	if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
	ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
	drawlist->PushClipRect(canvas_p0, canvas_p1, true);

	uint64_t totalframeTime = 0;
	std::vector<uint64_t> SampleTimes;
	std::vector<float> SampleWidths;
	std::vector<std::string> SampleNames;
	for (auto const& [SampleName, samples] : previousFrame)
	{
		totalframeTime += samples[0]->frameTime + 1;
		SampleTimes.push_back(samples[0]->frameTime + 1);
		SampleNames.push_back(SampleName);
	}

	float MinBlockWidth = canvas_sz.x / totalframeTime;
	for (int i = 0; i < SampleTimes.size(); i++) { SampleWidths.push_back(SampleTimes[i] * MinBlockWidth); }

	ImGui::LabelText("Total Frame Time", std::to_string(totalframeTime).c_str());
	ImGui::LabelText("Window Width / Total Frame Time", std::to_string(MinBlockWidth).c_str());

	float TotalBlockWidthSoFar = 0;
	int SampleCount = previousFrame.size();
	const ImU32 col_outline_base = ImGui::GetColorU32(ImGuiCol_PlotHistogram) & 0x7FFFFFFF;
	const ImU32 col_base = ImGui::GetColorU32(ImGuiCol_PlotHistogram) & 0x77FFFFFF;

	for (int i = 0; i < SampleCount; i++)
	{
		float ThisBlockWidth = SampleWidths[i];

		const ImVec2 minPos = ImVec2(canvas_p0.x + TotalBlockWidthSoFar, canvas_p0.y + 100);
		const ImVec2 maxPos = ImVec2(canvas_p0.x + TotalBlockWidthSoFar + ThisBlockWidth, canvas_p0.y + 200);
		drawlist->AddRectFilled(minPos, maxPos, col_base, GImGui->Style.FrameRounding);
		drawlist->AddRect(minPos, maxPos, col_outline_base);

		ImGui::RenderText(ImVec2(minPos.x + 10, minPos.y + 10), SampleNames[i].c_str());
		ImGui::RenderText(ImVec2(minPos.x + 10, minPos.y + 20), std::to_string(SampleTimes[i] - 1).c_str());

		TotalBlockWidthSoFar += ThisBlockWidth;
	}

	drawlist->PopClipRect();

	ImGui::End();
}

void DrawHierarchy()
{
	ImGui::Begin("Hierarchy");

	const std::vector<Pawn*>& Hierarchy = Hierarchy::INSTANCE().GetHierarchyList();
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;

	for (Pawn* pawn : Hierarchy)
	{
		bool isNodeOpen = ImGui::TreeNodeEx(std::to_string(pawn->ID).c_str(), nodeFlags, std::to_string(pawn->ID).c_str());

		if (ImGui::IsItemClicked()) { std::cout << "Selected object is " << std::to_string(pawn->ID).c_str() << std::endl; }

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("_TREENODE", pawn, sizeof(Pawn));
			ImGui::Text("This is a drap and drop source");
			ImGui::EndDragDropSource;
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_TREENODE"))
			{
				IM_ASSERT(payload->DataSize == sizeof(Pawn));
				Pawn* PayloadAsPawn = static_cast<Pawn*>(payload->Data);
				std::cout << PayloadAsPawn->ID << " on top of root" << std::endl;
			}
			ImGui::EndDragDropSource();
		}

		if (isNodeOpen)
		{
			for (int i = 0; i < 5; i++)
			{
				std::string itemName = "Child " + std::to_string(i);
				if (ImGui::TreeNodeEx(itemName.c_str(), nodeFlags, itemName.c_str())) {ImGui::TreePop(); }
			}
			ImGui::TreePop();
		}
	}

	ImGui::End();
}


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

	Player player(rendere, "./../Assets/Sprites/mario-idle.bmp", 100, 200, true);
	Pawn platform(rendere, "./../Assets/platform-test.bmp", 100, 600, true);
	Monster enemy(rendere, "./../Assets/Sprites/monstertrans.bmp", 400, 486, true);

	SDL_Surface* sprite1 = SDL_LoadBMP("./../Assets/Sprites/mario-1.bmp");
	SDL_Surface* sprite2 = SDL_LoadBMP("./../Assets/Sprites/mario-2.bmp");
	SDL_Surface* sprite3 = SDL_LoadBMP("./../Assets/Sprites/mario-3.bmp");
	SDL_Surface* sprite4 = SDL_LoadBMP("./../Assets/Sprites/mario-4.bmp");
	SDL_Surface* sprite5 = SDL_LoadBMP("./../Assets/Sprites/mario-5.bmp");
	SDL_Surface* sprite6 = SDL_LoadBMP("./../Assets/Sprites/mario-6.bmp");
	SDL_Surface* jumpSprite = SDL_LoadBMP("./../Assets/Sprites/mario-jump.bmp");

	std::vector<SDL_Surface*> colourKeySprites = { sprite1, sprite2, sprite3, sprite4, sprite5, sprite6 };

	for (int i = 0; i < colourKeySprites.size(); i++)
	{
		Uint32 colourKey = SDL_MapSurfaceRGBA(colourKeySprites[i], 255, 0, 255, 0);
		SDL_SetSurfaceColorKey(colourKeySprites[i], true, colourKey);
	}

	Uint32 colourKey = SDL_MapSurfaceRGBA(jumpSprite, 255, 0, 255, 0);
	SDL_SetSurfaceColorKey(jumpSprite, true, colourKey);

	SDL_Texture* texture1 = SDL_CreateTextureFromSurface(rendere.get(), sprite1);
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(rendere.get(), sprite2);
	SDL_Texture* texture3 = SDL_CreateTextureFromSurface(rendere.get(), sprite3);
	SDL_Texture* texture4 = SDL_CreateTextureFromSurface(rendere.get(), sprite4);
	SDL_Texture* texture5 = SDL_CreateTextureFromSurface(rendere.get(), sprite5);
	SDL_Texture* texture6 = SDL_CreateTextureFromSurface(rendere.get(), sprite6);
	SDL_Texture* jumpTexture = SDL_CreateTextureFromSurface(rendere.get(), jumpSprite);
	std::vector<SDL_Texture*> moveSprites = { texture1, texture2, texture3, texture4, texture5, texture6 };
	std::vector<SDL_Texture*> otherSprites = { jumpTexture };

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
	std::shared_ptr<BitmapComponent> temp = std::make_shared<BitmapComponent>(rendere, "./../Assets/Sprites/monster.bmp", 300, 200, false, &gameObject);
	gameObject.AddComponent(temp);
	gameObject.transform.Location.x = 500;
	gameObject.transform.Location.y = 200;
	RootTransform.AddChild(&gameObject.transform);

	GameObject gameObject2;
	std::shared_ptr<BitmapComponent> temp2 = std::make_shared<BitmapComponent>(rendere, "./../Assets/Sprites/monstertrans.bmp", 300, 200, false, &gameObject2);
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
	
	std::shared_ptr<ScriptComponent> scriptTest = std::make_shared<ScriptComponent>("./../luaSrc/ComponentTest.lua", &gameObject);
	//gameObject.AddComponent(scriptTest);

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

	irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
	if (!soundEngine)
	{
		DebugPrintF("Could not start up sound engine\n");
		std::cerr << "Could not start up sound engine\n" << std::endl;
	}
	else
	{
		DebugPrintF("Sound engine started\n");
		std::cout << "Sound engine started\n" << std::endl;
	}
	soundEngine->play2D("./../Libraries/irrKlang/media/getout.ogg", true);

	std::vector<Pawn*> Colliders;
	Colliders.push_back(&platform);
	Colliders.push_back(&enemy);

	AssetWindow window(rendere);

	bool IsRunning = true;

	SavePlayerToJson(player);
	SaveLoadSystem::INSTANCE().SaveGame("SavegameGO.json", gameObject);

	int FrameNumber = 0;

	while (IsRunning)
	{
		ProfilerSystem::Instance().StartFrame();


		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			Input::INSTANCE().UpdateMouse(e);
			ImGui_ImplSDL3_ProcessEvent(&e);
			switch (e.type) {
			case SDL_EVENT_KEY_DOWN:
				if (e.key.scancode == SDL_SCANCODE_1)
					SavePlayerToJson(player);
				if (e.key.scancode == SDL_SCANCODE_2)
					LoadPlayerFromJson(player);
				if (e.key.scancode == SDL_SCANCODE_O)
				{
					SaveLoadSystem::INSTANCE().SaveGame("SavegameGO.json", gameObject);
					std::cout << "Saved to SavegameGO.json\n";
				}
				if (e.key.scancode == SDL_SCANCODE_P)
				{
					SaveLoadSystem::INSTANCE().LoadGame("SavegameGO.json", gameObject, rendere);
					std::cout << "Loaded from SavegameGO.json\n";
				}
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
				LoadPlayerFromJson(player);
				SaveLoadSystem::INSTANCE().LoadGame("SavegameGO.json", gameObject, rendere);

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

		RootTransform.UpdateTransform(Transform{});
		gameObject.Update();
		gameObject2.Update();
		enemy.Subscribe("Test");

		SDL_RenderTexture(rendere.get(), backgroundTexture, NULL, NULL);
		Hierarchy::INSTANCE().DrawHierarchyItems();
		PROFILE("PlayerRender");
		//player.Draw();
		if ((player.isMovingRight == true || player.isMovingLeft == true) && player.Grounded) { player.DrawAnimation(moveSprites, FrameNumber, player.GetX(), player.GetY()); }
		else if (!player.Grounded)
			player.DrawAnimation(otherSprites, FrameNumber, player.GetX(), player.GetY());
		else { player.Draw(); }
		platform.Draw();
		enemy.Draw();
		//RendererSystem::Render(ecs, rendere);
		MovementSystem::UpdatePositions(ecs);

		DrawProfileData(io);
		DrawHierarchy();

		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		ImGui::Render();
		SDL_SetRenderScale(rendere.get(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		SDL_SetRenderDrawColorFloat(rendere.get(), clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), rendere.get());

		SDL_RenderPresent(rendere.get());

		Input::INSTANCE().LateUpdate();

		SDL_Delay(16);

		ProfilerSystem::Instance().EndFrame();
		FrameNumber++;
	}
	ProfilerSystem::Instance().WriteDataToCSV();

	SDL_DestroyWindow(win);
	SDL_Quit();
	soundEngine->drop();
	return 0;
}

