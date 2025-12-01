#include "GameObject.h"

void GameObject::AddComponent(std::shared_ptr<I_ComponentBase> component)
{
	Components.push_back(component);
}

void GameObject::RemoveComponent(std::shared_ptr<I_ComponentBase> component)
{
	auto it = std::remove(Components.begin(), Components.end(), component);
	if (it != Components.end()) Components.erase(it, Components.end());
}

void GameObject::Update()
{
	for (const auto& component : Components) component->Update();
}
