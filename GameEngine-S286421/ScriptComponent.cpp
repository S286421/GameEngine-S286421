#include "ScriptComponent.h"

/// <summary>
/// Initialises the ScriptComponent; assigns ScriptPath to FilePath, and calls ScriptComponent::LoadScript()
/// </summary>
/// <param name="FilePath"></param>
/// <param name="ParentObj"></param>
ScriptComponent::ScriptComponent(const std::string FilePath, GameObject* ParentObj) : I_ComponentBase(ParentObj)
{
	ScriptPath = FilePath;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
	LoadScript();
}

/// <summary>
/// Attempts to load the lua file at ScriptPath (throws an error if the file cannot be found)
/// </summary>
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

/// <summary>
/// Updates the variables used by the lua file, and calls the update function in the lua file
/// </summary>
void ScriptComponent::Update()
{
	reloadIfChanged();

	lua.new_usertype<SDL_Point>("SDL_Point", "x", &SDL_Point::x, "y", &SDL_Point::y);

	lua.new_usertype<Transform>("Transform", "GetX", &Transform::GetX, "Location", &Transform::Location);

	lua.new_usertype<GameObject>("parentObject", "Transform", &GameObject::transform);

	//
	int i = (sin(SDL_GetTicks() / 500) * 2);
	//lua.new_usertype<int>("Movement", "ToMove", &i);

	lua["parentObject"] = ParentObject;
	lua["move"] = i;

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

/// <summary>
/// Allows for the lua file to be changed during runtime
/// </summary>
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

/// <summary>
/// Saves the ScriptPath and Type() to BitmapSaveData and returns it
/// </summary>
/// <returns></returns>
nlohmann::json ScriptComponent::Save() const
{
	nlohmann::json BitmapSaveData;

	BitmapSaveData[Type()] = { {"scriptPath", ScriptPath}, {"type", Type()} };

	return BitmapSaveData;
}

/// <summary>
/// Loads data from ScriptPath, and calls ScriptComponent::LoadScript()
/// </summary>
/// <param name="LoadData"></param>
/// <param name="renderer"></param>
void ScriptComponent::Load(nlohmann::json LoadData, std::shared_ptr<SDL_Renderer> renderer)
{
	ScriptPath = LoadData["scriptPath"].get<std::string>();
	LoadScript();
}
