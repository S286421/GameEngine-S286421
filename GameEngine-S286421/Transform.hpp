#pragma once
#include <SDL3/SDL.h>
#include <vector>
struct Transform
{
public:
	std::vector<Transform*> Children;
	SDL_Point Location = {0,0};
	SDL_Point WorldLocation;

	void AddChild(Transform* child)
	{
		Children.push_back(child);
	}

	void removeChild(Transform* child)
	{
		auto it = std::remove(Children.begin(), Children.end(), child);
		if (it != Children.end())
			Children.erase(it, Children.end());
	}

	void UpdateTransform(const Transform& parentTransform)
	{
		WorldLocation.x = Location.x + parentTransform.Location.x;
		WorldLocation.y = Location.y + parentTransform.Location.y;

		for (Transform* child : Children)
		{
			child->UpdateTransform(*this);
			
		}
	}

	int GetX()
	{
		return Location.x;
	}
};