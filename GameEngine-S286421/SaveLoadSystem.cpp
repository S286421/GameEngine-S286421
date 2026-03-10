#include "SaveLoadSystem.h"

/// <summary>
/// Creates a save/load system instance and returns it; used to call the save/load system in other files
/// </summary>
/// <returns></returns>
SaveLoadSystem& const SaveLoadSystem::INSTANCE()
{
	if (!SaveLoadSystem::_instance)
		SaveLoadSystem::_instance = new SaveLoadSystem();

	return *SaveLoadSystem::_instance;
}

/// <summary>
/// Finds the file from the given filename (or creates it if not found) and calls GameObject::Save() for the object ToSave
/// </summary>
/// <param name="filename"></param>
/// <param name="ToSave"></param>
void SaveLoadSystem::SaveGame(const std::string& filename, const GameObject& ToSave)
{
	GameObject toSave = ToSave;
	std::ofstream file(filename);
	file << ToSave.Save().dump(4);
	file.close();
}

/// <summary>
/// If the given filename can be found, calls the GameObject::Load() function using the GameObject ToLoad, the given renderer, and the loadData in the file
/// </summary>
/// <param name="filename"></param>
/// <param name="ToLoad"></param>
/// <param name="renderer"></param>
void SaveLoadSystem::LoadGame(const std::string& filename, GameObject& ToLoad, std::shared_ptr<SDL_Renderer> renderer)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "Failed to open SavegameGO.json\n";
	}

	nlohmann::json loadData;
	file >> loadData;
	file.close();

	ToLoad.Load(loadData, renderer);
}
SaveLoadSystem* SaveLoadSystem::_instance = nullptr;
