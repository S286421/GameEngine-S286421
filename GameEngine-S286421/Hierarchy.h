#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Pawn.h"

class SDL_Renderer;

class Hierarchy
{
	std::shared_ptr<SDL_Renderer> renderer;
public:
	void Init(const std::shared_ptr<SDL_Renderer>& rendererPtr)
	{
		renderer = rendererPtr;
	}

	Hierarchy()
	{
	}

	static Hierarchy* _instance;
	static Hierarchy& const INSTANCE();

	std::vector<Pawn*> HierarchyList;

	Pawn* AddGameObject(const std::string path, int x, int y, bool isTransparent);

	void DrawHierarchyItems();
};

