#include "BitmapComponent.h"
#include "GameObject.h"
void BitmapComponent::Update()
{
	if (_bitmap)
		_bitmap->Draw(ParentObject->transform.WorldLocation.x, ParentObject->transform.WorldLocation.y);
}

nlohmann::json BitmapComponent::Save() const
{
	nlohmann::json BitmapSaveData;

	BitmapSaveData[Type()] = { {"path", _bitmap->GetPath()}, {"x", _bitmap->GetX()}, {"y", _bitmap->GetY()}, {"isTransparent", _bitmap->getIsTransparent()}, {"width", _bitmap->GetWidth()}, {"height", _bitmap->GetHeight()}, {"type", Type()} };

	return BitmapSaveData;
}

void BitmapComponent::Load(nlohmann::json LoadData, std::shared_ptr<SDL_Renderer> renderer)
{
	const std::string path = LoadData["path"].get<std::string>();
	int x = LoadData["x"];
	int y = LoadData["y"];
	bool isTransparent = LoadData["isTransparent"];
	_bitmap = std::make_shared<Bitmap>(renderer, path, x, y, isTransparent);
}
