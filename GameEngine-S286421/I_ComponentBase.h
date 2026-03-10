#pragma once
#include "ISaveLoadable.h"

class GameObject;

class I_ComponentBase : public ISaveLoadable
{
public:
	GameObject* ParentObject;

	virtual ~I_ComponentBase() = 0;
	virtual void Update() = 0;

	/// <summary>
	/// Initialises the I_ComponentBase; defines the ParentObject GameObject as the given variable
	/// </summary>
	/// <param name="Parent"></param>
	I_ComponentBase(GameObject* Parent)
	{
		ParentObject = Parent;
	}

	/// <summary>
	/// defined in GameObject as GameObject::Save()
	/// </summary>
	/// <returns></returns>
	virtual nlohmann::json Save() const = 0;

	/// <summary>
	/// defined in GameObject as GameObject::Load()
	/// </summary>
	/// <param name="LoadData"></param>
	/// <param name="renderer"></param>
	virtual void Load(nlohmann::json LoadData, std::shared_ptr<SDL_Renderer> renderer) = 0;

	/// <summary>
	/// defined in BitmapComponent as BitmapComponent::Type()
	/// </summary>
	/// <returns></returns>
	virtual std::string Type() const = 0;
};

