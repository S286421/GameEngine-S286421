#include "ScriptComponent.h"

ScriptComponent::ScriptComponent(const std::string FilePath, GameObject* ParentObj) : I_ComponentBase(ParentObj)
{
	ScriptPath = FilePath;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
	LoadScript();
}

void ScriptComponent::LoadScript()
{
	try
	{
		luaScriptComponent = lua.script_file(ScriptPath);
		LastUpdated = std::filesystem::last_write_time(ScriptPath);
		std::cout << "[C++]Loading Lua " << ScriptPath << std::endl;
	}
	catch (const sol::error& e)
	{
		std::cerr << "[c++] lua error " << e.what() << std::endl;
	}
}

void ScriptComponent::Update()
{
	reloadIfChanged();

	lua.new_usertype<SDL_Point>("SDL_Point", "x", &SDL_Point::x, "y", &SDL_Point::y);

	lua.new_usertype<Transform>("Transform", "GetX", &Transform::GetX, "Location", &Transform::Location);

	lua.new_usertype<GameObject>("parentObject", "Transform", &GameObject::transform);

	lua["parentObject"] = ParentObject;

	try
	{
		sol::function update = luaScriptComponent["Update"];
		update();
	}
	catch (const sol::error& e)
	{
		std::cerr << "[c++] lua error " << e.what() << std::endl;
	}
}

void ScriptComponent::reloadIfChanged()
{
	std::filesystem::file_time_type newTime = std::filesystem::last_write_time(ScriptPath);
	if (newTime != LastUpdated)
	{
		std::cout << "[C++][Lua] code change detected in: " << ScriptPath << std::endl;
		std::cout << "[C++][Lua] Processing change..." << std::endl;
		LoadScript();
	}
}
