#pragma once
#include "I_ComponentBase.h"
#include "Sol/sol.hpp"
#include "SDL3/SDL.h"
#include "Transform.hpp"
#include "GameObject.h"
#include <filesystem>

class ScriptComponent : public I_ComponentBase
{
private:
	sol::state lua;
	sol::table luaScriptComponent;
	std::string ScriptPath;

	std::filesystem::file_time_type LastUpdated;

public:
	ScriptComponent(const std::string FilePath, GameObject* ParentObj);

	void Update() override;

private:
	void reloadIfChanged();

	void LoadScript();

public:
	nlohmann::json Save() const override;
	void Load(nlohmann::json LoadData, std::shared_ptr<SDL_Renderer> renderer) override;
	std::string Type() const override { return "ScriptComponent"; }

	ScriptComponent(GameObject* ParentObject) : I_ComponentBase(ParentObject) {};
};

