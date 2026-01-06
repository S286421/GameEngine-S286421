#include "SaveLoadSystem.h"

SaveLoadSystem& const SaveLoadSystem::INSTANCE()
{
	if (!SaveLoadSystem::_instance)
		SaveLoadSystem::_instance = new SaveLoadSystem();

	return *SaveLoadSystem::_instance;
}
void SaveLoadSystem::SaveGame(const std::string& filename, const GameObject& ToSave)
{
	GameObject toSave = ToSave;
	std::ofstream file(filename);
	file << ToSave.Save().dump(4);
	file.close();
}
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
