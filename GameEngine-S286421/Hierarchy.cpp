#include "Hierarchy.h"

Hierarchy* Hierarchy::_instance = nullptr;
Hierarchy& const Hierarchy::INSTANCE()
{
	if (!Hierarchy::_instance)
		Hierarchy::_instance = new Hierarchy();

	return *Hierarchy::_instance;
}

void Hierarchy::AddGameObject(Pawn* pawn)
{
	HierarchyList.push_back(pawn);
}

Pawn* Hierarchy::AddGameObject(std::string path, int x, int y, bool isTransparent)
{
	Pawn* newPawn = new Pawn(renderer, path, x, y, isTransparent, "");
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

void Hierarchy::DrawHierarchy()
{
	ImGui::Begin("Hierarchy");

	const std::vector<Pawn*>& Hierarchy = Hierarchy::INSTANCE().GetHierarchyList();
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;

	for (Pawn* pawn : Hierarchy)
	{
		bool isNodeOpen = ImGui::TreeNodeEx(pawn->PawnName.c_str(), nodeFlags, pawn->PawnName.c_str());

		if (ImGui::IsItemClicked()) { std::cout << "Selected object is " << pawn->PawnName.c_str() << std::endl; }

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("_TREENODE", pawn, sizeof(Pawn));
			ImGui::Text("This is a drag and drop source");
			ImGui::EndDragDropSource;
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_TREENODE"))
			{
				IM_ASSERT(payload->DataSize == sizeof(Pawn));
				Pawn* PayloadAsPawn = static_cast<Pawn*>(payload->Data);
				std::cout << PayloadAsPawn->PawnName << " on top of root" << std::endl;
			}
			ImGui::EndDragDropSource();
		}

		if (isNodeOpen)
		{
			ImGui::TreePop();
		}
	}

	ImGui::End();
}
