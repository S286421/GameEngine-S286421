#pragma once
#include <memory>
#include <string>
#include <vector>
#include <imgui.h>
#include "Pawn.h"

class SDL_Renderer;

class Hierarchy
{
	std::shared_ptr<SDL_Renderer> renderer;
public:
	/// <summary>
	/// Initialises the Hierarchy; sets the Hierarchy class' renderer variable to the given rendererPtr
	/// </summary>
	/// <param name="rendererPtr"></param>
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

	void AddGameObject(Pawn* pawn);
	Pawn* AddGameObject(std::string path, int x, int y, bool isTransparent);

	void DrawHierarchyItems();
	void UpdateHierarchyItems();

	/// <summary>
	/// Returns the HierarchyList
	/// </summary>
	/// <returns></returns>
	std::vector<Pawn*> GetHierarchyList() const { return HierarchyList; }

	void DrawHierarchy();
};

