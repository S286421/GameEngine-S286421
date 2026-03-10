#include "GameObject.h"

/// <summary>
/// Adds the given component to the Components vector
/// </summary>
/// <param name="component"></param>
void GameObject::AddComponent(std::shared_ptr<I_ComponentBase> component)
{
	Components.push_back(component);
}

/// <summary>
/// Removes the given component from the Components vector
/// </summary>
/// <param name="component"></param>
void GameObject::RemoveComponent(std::shared_ptr<I_ComponentBase> component)
{
	auto it = std::remove(Components.begin(), Components.end(), component);
	if (it != Components.end()) Components.erase(it, Components.end());
}

/// <summary>
/// Call the I_ComponentBase::Update() function for all components in the Components vector
/// </summary>
void GameObject::Update()
{
	for (const auto& component : Components) component->Update();
}

/// <summary>
/// Saves the x position, y position, and all attached components for a game object, and returns the SaveData
/// </summary>
/// <returns></returns>
nlohmann::json GameObject::Save() const
{
	nlohmann::json SaveData;

	SaveData["Transform"] = { {"LocationX", transform.Location.x}, {"LocationY", transform.Location.y} };

	for (std::shared_ptr<I_ComponentBase>Component : Components)
		SaveData["Components"].push_back(Component->Save());

	return SaveData;
}

/// <summary>
/// Loads the x position, y position, and all attached components for a game object from the given LoadData file
/// </summary>
/// <param name="LoadData"></param>
/// <param name="renderer"></param>
void GameObject::Load(nlohmann::json LoadData, std::shared_ptr<SDL_Renderer> renderer)
{
	Components.clear();

	transform.Location.x = LoadData["Transform"]["LocationX"];
	transform.Location.y = LoadData["Transform"]["LocationY"];

	for (auto& componentData : LoadData["Components"])
	{
		std::string type = componentData.begin().value()["type"];
		if (type == "BitmapComponent")
		{
			std::shared_ptr<BitmapComponent> bitmapComp = std::make_shared<BitmapComponent>(this);
			bitmapComp->Load(componentData.begin().value(), renderer);
			AddComponent(bitmapComp);
		}
		else if (type == "ScriptComponent")
		{
			std::shared_ptr<ScriptComponent> scriptComp = std::make_shared<ScriptComponent>(this);
			scriptComp->Load(componentData.begin().value(), renderer);
			AddComponent(scriptComp);
		}
	}
}
