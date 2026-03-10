#pragma once
#include "Transform.hpp"
#include <vector>
#include "I_ComponentBase.h"
#include <memory>
#include "BitmapComponent.h"
#include "ScriptComponent.h"

template<typename T>
concept componentType = std::is_same_v< T, I_ComponentBase >;

class GameObject : public ISaveLoadable
{
public:
	Transform transform;

	std::vector<std::shared_ptr<I_ComponentBase>> Components;

	void AddComponent(std::shared_ptr<I_ComponentBase> component);
	void RemoveComponent(std::shared_ptr<I_ComponentBase> component);

	void Update();

	template<typename componentType>
	
	/// <summary>
	///	Returns a dynamic_cast of componentType variables that match the componentType of obj; returns nullptr if none are found
	/// </summary>
	/// <returns></returns>
	componentType* GetComponentByType()
	{
		auto it = std::find_if(Components.begin(), Components.end(), [](const std::shared_ptr<I_ComponentBase>& obj)
			{
				return dynamic_cast<componentType*>(obj.get()) != nullptr;
			}
		);
		
		if (it != Components.end())
			return dynamic_cast<componentType*> ((*it).get());

		return nullptr;
	}

	nlohmann::json Save() const override;
	void Load(nlohmann::json LoadData, std::shared_ptr<SDL_Renderer> renderer) override;
};

