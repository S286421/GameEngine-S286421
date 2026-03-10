#include "BitmapComponent.h"
#include "GameObject.h"

/// <summary>
/// Calls the Bitmap::Draw(x, y) function for the ParentObject it is attached to
/// </summary>
void BitmapComponent::Update()
{
	if (_bitmap)
		_bitmap->Draw(ParentObject->transform.WorldLocation.x, ParentObject->transform.WorldLocation.y);
}

/// <summary>
/// Handles saving the data of a bitmap, and then returns it
/// </summary>
/// <returns></returns>
nlohmann::json BitmapComponent::Save() const
{
	nlohmann::json BitmapSaveData;

	BitmapSaveData[Type()] = { {"path", _bitmap->GetPath()}, {"x", _bitmap->GetX()}, {"y", _bitmap->GetY()}, {"isTransparent", _bitmap->getIsTransparent()}, {"width", _bitmap->GetWidth()}, {"height", _bitmap->GetHeight()}, {"type", Type()} };

	return BitmapSaveData;
}

/// <summary>
/// Creates a bitmap from the LoadData given
/// </summary>
/// <param name="LoadData"></param>
/// <param name="renderer"></param>
void BitmapComponent::Load(nlohmann::json LoadData, std::shared_ptr<SDL_Renderer> renderer)
{
	const std::string path = LoadData["path"].get<std::string>();
	int x = LoadData["x"];
	int y = LoadData["y"];
	bool isTransparent = LoadData["isTransparent"];
	_bitmap = std::make_shared<Bitmap>(renderer, path, x, y, isTransparent);
}
