#pragma once
#include"I_ComponentBase.h"
#include <memory>
#include "Bitmap.h"
class BitmapComponent : public I_ComponentBase
{
	std::shared_ptr<Bitmap> _bitmap;
public:

	/// <summary>
	/// Initialises the BitmapComponent; creates and std::make_shared<Bitmap> using the given variables
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="path"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="isTransparent"></param>
	/// <param name="parentObject"></param>
	BitmapComponent(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent, GameObject* parentObject): I_ComponentBase(parentObject)
	{
		_bitmap = std::make_shared<Bitmap>(renderer, path, x, y, isTransparent);
	}
	~BitmapComponent() override {};
	void Update() override;

	nlohmann::json Save() const override;
	void Load(nlohmann::json LoadData, std::shared_ptr<SDL_Renderer> renderer) override;
	/// <summary>
	/// Returns the string "BitmapComponent"; used for searching for object type when saving
	/// </summary>
	/// <returns></returns>
	std::string Type() const override { return "BitmapComponent"; }

	BitmapComponent(GameObject* parentObject) : I_ComponentBase(parentObject) {};
};

