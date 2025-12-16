#include "Hierarchy.h"

Hierarchy* Hierarchy::_instance = nullptr;
Hierarchy& const Hierarchy::INSTANCE()
{
	if (!Hierarchy::_instance)
		Hierarchy::_instance = new Hierarchy();

	return *Hierarchy::_instance;
}

Pawn* Hierarchy::AddGameObject(const std::string path, int x, int y, bool isTransparent)
{
	Pawn* newPawn = new Pawn(renderer, path, x, y, isTransparent);
	HierarchyList.push_back(newPawn);
	return newPawn;
}

void Hierarchy::DrawHierarchyItems()
{
	for (int i = 0; i < HierarchyList.size(); i++)
	{
		HierarchyList[i]->Draw();
	}
}
