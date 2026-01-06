#pragma once
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include "json.hpp"
#include "GameObject.h"
class GameObject;
struct SDL_Renderer;

class SaveLoadSystem
{
public:
	static SaveLoadSystem* _instance;
	static SaveLoadSystem& const INSTANCE();

	void SaveGame(const std::string& filename, const GameObject& ToSave);
	void LoadGame(const std::string& filename, GameObject& ToLoad, std::shared_ptr<SDL_Renderer> renderer);
};

